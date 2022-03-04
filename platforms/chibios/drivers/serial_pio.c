// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "serial_protocol.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"

#if !defined(MCU_RP)
#    error PIO Driver is only available for Raspberry Pi 2040 MCUs!
#endif

#define MSG_PIO_ERROR (msg_t) - 3

#if defined(SERIAL_PIO_USE_PIO0)
static PIO pio = pio0;
#elif defined(SERIAL_PIO_USE_PIO1)
static PIO pio = pio1;
#else
#    define SERIAL_PIO_USE_PIO1
static PIO pio = pio1;
#endif

static void pio_serve_interrupt(void);

#if defined(SERIAL_PIO_USE_PIO0)

OSAL_IRQ_HANDLER(RP_PIO0_IRQ_0_HANDLER) {
    OSAL_IRQ_PROLOGUE();
    pio_serve_interrupt();
    OSAL_IRQ_EPILOGUE();
}

#else

OSAL_IRQ_HANDLER(RP_PIO1_IRQ_0_HANDLER) {
    OSAL_IRQ_PROLOGUE();
    pio_serve_interrupt();
    OSAL_IRQ_EPILOGUE();
}

#endif

#define uart_tx_wrap_target 0
#define uart_tx_wrap 3

// clang-format off
static const uint16_t uart_tx_program_instructions[] = {
            //     .wrap_target
    0x9fa0, //  0: pull   block           side 1 [7]
    0xf727, //  1: set    x, 7            side 0 [7]
    0x6001, //  2: out    pins, 1
    0x0642, //  3: jmp    x--, 2                 [6]
            //     .wrap
};
// clang-format on

static const pio_program_t uart_tx_program = {
    .instructions = uart_tx_program_instructions,
    .length       = 4,
    .origin       = -1,
};

#define uart_rx_wrap_target 0
#define uart_rx_wrap 8

// clang-format off
static const uint16_t uart_rx_program_instructions[] = {
            //     .wrap_target
    0x2020, //  0: wait   0 pin, 0                   
    0xea27, //  1: set    x, 7                   [10]
    0x4001, //  2: in     pins, 1                    
    0x0642, //  3: jmp    x--, 2                 [6] 
    0x00c8, //  4: jmp    pin, 8                     
    0xc020, //  5: irq    wait 0                     
    0x20a0, //  6: wait   1 pin, 0                   
    0x0000, //  7: jmp    0                          
    0x8020, //  8: push   block                      
            //     .wrap
};
// clang-format on

static const pio_program_t uart_rx_program = {
    .instructions = uart_rx_program_instructions,
    .length       = 9,
    .origin       = -1,
};

thread_reference_t rx_thread        = NULL;
const static int   rx_state_machine = 1;

thread_reference_t tx_thread        = NULL;
const static int   tx_state_machine = 0;

void pio_serve_interrupt(void) {
    uint32_t mask = pio->ints0;

    // The RX FIFO is not empty any more, therefore wake any sleeping rx thread
    if (mask & PIO_IRQ0_INTF_SM1_RXNEMPTY_BITS) {
        // Disable rx not empty interrupt
        pio_set_irq0_source_enabled(pio, pis_sm1_rx_fifo_not_empty, false);

        osalSysLockFromISR();
        osalThreadResumeI(&rx_thread, MSG_OK);
        osalSysUnlockFromISR();
    }

    // IRQ 0 is set on framing or break errors by the rx state machine
    if (pio_interrupt_get(pio, 0UL)) {
        pio_interrupt_clear(pio, 0UL);

        osalSysLockFromISR();
        osalThreadResumeI(&rx_thread, MSG_PIO_ERROR);
        osalSysUnlockFromISR();
    }

    // The TX FIFO is not full any more, therefore wake any sleeping tx thread
    if (mask & PIO_IRQ0_INTF_SM0_TXNFULL_BITS) {
        // Disable tx not full interrupt
        pio_set_irq0_source_enabled(pio, pis_sm0_tx_fifo_not_full, false);
        osalSysLockFromISR();
        osalThreadResumeI(&tx_thread, MSG_OK);
        osalSysUnlockFromISR();
    }
}

/**
 * @brief Clear the RX and TX hardware FIFOs of the state machines.
 */
inline void driver_clear(void) {
    osalSysLock();
    pio_sm_clear_fifos(pio, rx_state_machine);
    pio_sm_clear_fifos(pio, tx_state_machine);
    osalSysUnlock();
}

static inline msg_t sync_tx(sysinterval_t timeout) {
    msg_t msg = MSG_OK;
    osalSysLock();
    while (pio_sm_is_tx_fifo_full(pio, tx_state_machine)) {
        pio_set_irq0_source_enabled(pio, pis_sm0_tx_fifo_not_full, true);
        msg = osalThreadSuspendTimeoutS(&tx_thread, timeout);
        if (msg < MSG_OK) {
            break;
        }
    }
    osalSysUnlock();
    return msg;
}

static inline size_t pio_send(const uint8_t* source, const size_t size) {
    size_t send = 0;
    while (true) {
        if (pio_sm_is_tx_fifo_full(pio, tx_state_machine)) {
            break;
        }
        if (send >= size) {
            break;
        }
        pio_sm_put(pio, tx_state_machine, (uint32_t)(*source));
        source++;
        send++;
    }
    return send;
}

/**
 * @brief Blocking send of buffer with timeout.
 *
 * @return true Send success.
 * @return false Send failed.
 */
inline bool send(const uint8_t* source, const size_t size) {
    size_t send_total = 0U;
    msg_t  msg;

    while (send_total < size) {
        size_t send;
        msg = sync_tx(TIME_MS2I(SERIAL_USART_TIMEOUT));
        if (msg < MSG_OK) {
            return false;
        }

        osalSysLock();
        send = pio_send(source, size - send_total);
        osalSysUnlock();
        source += send;
        send_total += send;
    }

    return send_total == size;
}

static inline msg_t sync_rx(sysinterval_t timeout) {
    msg_t msg = MSG_OK;
    osalSysLock();
    while (pio_sm_is_rx_fifo_empty(pio, rx_state_machine)) {
        pio_set_irq0_source_enabled(pio, pis_sm1_rx_fifo_not_empty, true);
        msg = osalThreadSuspendTimeoutS(&rx_thread, timeout);
        if (msg < MSG_OK) {
            break;
        }
    }
    osalSysUnlock();
    return msg;
}

static inline size_t pio_read(uint8_t* destination, const size_t size) {
    size_t received = 0;
    while (true) {
        if (pio_sm_is_rx_fifo_empty(pio, rx_state_machine)) {
            break;
        }
        if (received >= size) {
            break;
        }
        *destination++ = pio_sm_get(pio, rx_state_machine) >> 24UL;
        received++;
    }
    return received;
}

static inline bool receive_impl(uint8_t* destination, const size_t size, sysinterval_t timeout) {
    size_t read_total = 0U;

    while (read_total < size) {
        size_t read;
        msg_t  msg = sync_rx(timeout);
        if (msg < MSG_OK) {
            //  dprintf("failed: %04x, inte: %04x\n", msg, pio->inte0);
            return false;
        }
        osalSysLock();
        read = pio_read(destination, size - read_total);
        osalSysUnlock();
        read_total += read;
        destination += read;
    }

    return read_total == size;
}

/**
 * @brief  Blocking receive of size * bytes with timeout.
 *
 * @return true Receive success.
 * @return false Receive failed, e.g. by timeout.
 */
inline bool receive(uint8_t* destination, const size_t size) {
    return receive_impl(destination, size, TIME_MS2I(SERIAL_USART_TIMEOUT));
}

/**
 * @brief  Blocking receive of size * bytes.
 *
 * @return true Receive success.
 * @return false Receive failed.
 */
inline bool receive_blocking(uint8_t* destination, const size_t size) {
    return receive_impl(destination, size, TIME_INFINITE);
}

static inline void uart_tx_init(pin_t tx_pin) {
    uint pio_idx = pio_get_index(pio);
    uint offset  = pio_add_program(pio, &uart_tx_program);
    // Tell PIO to initially drive output-high on the selected pin, then map PIO
    // onto that pin with the IO muxes.
    pio_sm_set_pins_with_mask(pio, tx_state_machine, 1u << tx_pin, 1u << tx_pin);
    pio_sm_set_pindirs_with_mask(pio, tx_state_machine, 1u << tx_pin, 1u << tx_pin);

    palSetLineMode(tx_pin, pio_idx == 0 ? PAL_MODE_ALTERNATE_PIO0 : PAL_MODE_ALTERNATE_PIO1);

    pio_sm_config config = pio_get_default_sm_config();
    sm_config_set_wrap(&config, offset + uart_tx_wrap_target, offset + uart_tx_wrap);
    sm_config_set_sideset(&config, 2, true, false);
    // OUT shifts to right, no autopull
    sm_config_set_out_shift(&config, true, false, 32);
    // We are mapping both OUT and side-set to the same pin, because sometimes
    // we need to assert user data onto the pin (with OUT) and sometimes
    // assert constant values (start/stop bit)
    sm_config_set_out_pins(&config, tx_pin, 1);
    sm_config_set_sideset_pins(&config, tx_pin);
    // We only need TX, so get an 8-deep FIFO!
    sm_config_set_fifo_join(&config, PIO_FIFO_JOIN_TX);
    // SM transmits 1 bit per 8 execution cycles.
    float div = (float)clock_get_hz(clk_sys) / (8 * SERIAL_USART_SPEED);
    sm_config_set_clkdiv(&config, div);
    pio_sm_init(pio, tx_state_machine, offset, &config);
}

static inline void uart_rx_init(pin_t rx_pin) {
    uint pio_idx = pio_get_index(pio);
    uint offset  = pio_add_program(pio, &uart_rx_program);

    pio_sm_set_consecutive_pindirs(pio, rx_state_machine, rx_pin, 1, false);
    // pio_gpio_init(pio, rx_pin);
    // gpio_pull_up(rx_pin);

    palSetLineMode(rx_pin, (pio_idx == 0 ? PAL_MODE_ALTERNATE_PIO0 : PAL_MODE_ALTERNATE_PIO1) | PAL_RP_PAD_PUE);

    pio_sm_config config = pio_get_default_sm_config();
    sm_config_set_wrap(&config, offset + uart_rx_wrap_target, offset + uart_rx_wrap);
    sm_config_set_in_pins(&config, rx_pin); // for WAIT, IN
    sm_config_set_jmp_pin(&config, rx_pin); // for JMP
    // Shift to right, autopush disabled
    sm_config_set_in_shift(&config, true, false, 32);
    // Deeper FIFO as we're not doing any TX
    sm_config_set_fifo_join(&config, PIO_FIFO_JOIN_RX);
    // SM transmits 1 bit per 8 execution cycles.
    float div = (float)clock_get_hz(clk_sys) / (8 * SERIAL_USART_SPEED);
    sm_config_set_clkdiv(&config, div);
    pio_sm_init(pio, rx_state_machine, offset, &config);
}

static inline void pio_init(pin_t tx_pin, pin_t rx_pin) {
    uint pio_idx = pio_get_index(pio);

    /* Get PIOx peripheral out of reset state. */
    hal_lld_peripheral_reset(pio_idx == 0 ? RESETS_ALLREG_PIO0 : RESETS_ALLREG_PIO1);
    hal_lld_peripheral_unreset(pio_idx == 0 ? RESETS_ALLREG_PIO0 : RESETS_ALLREG_PIO1);

    pio_sm_claim(pio, tx_state_machine);
    uart_tx_init(tx_pin);

    pio_sm_claim(pio, rx_state_machine);
    uart_rx_init(rx_pin);

    // Enable error flag IRQ source for rx state machine
    pio_set_irq0_source_enabled(pio, pis_sm1_rx_fifo_not_empty, true);
    pio_set_irq0_source_enabled(pio, pis_sm0_tx_fifo_not_full, true);
    pio_set_irq0_source_enabled(pio, pis_interrupt0, true);

    // Enable PIO specific interrupt vector
#if defined(SERIAL_PIO_USE_PIO0)
    // TODO add RP_PIO0_IRQ_0_PRIORITY
    nvicEnableVector(RP_PIO0_IRQ_0_NUMBER, RP_IRQ_UART0_PRIORITY);
#else
    nvicEnableVector(RP_PIO1_IRQ_0_NUMBER, RP_IRQ_UART0_PRIORITY);
#endif

    pio_enable_sm_mask_in_sync(pio, (1 << tx_state_machine) | (1 << rx_state_machine));
    return;
}

/**
 * @brief PIO driver specific initialization function for the master side.
 */
void driver_master_init(void) {
#if defined(SERIAL_USART_FULL_DUPLEX)
    pin_t tx_pin = SERIAL_USART_TX_PIN;
    pin_t rx_pin = SERIAL_USART_RX_PIN;
#else
    pin_t tx_pin = SERIAL_USART_TX_PIN;
    pin_t rx_pin = SERIAL_USART_TX_PIN;
#endif

#if defined(SERIAL_USART_PIN_SWAP)
    pio_init(rx_pin, tx_pin);
#else
    pio_init(tx_pin, rx_pin);
#endif
}

/**
 * @brief PIO driver specific initialization function for the slave side.
 */
void driver_slave_init(void) {
#if defined(SERIAL_USART_FULL_DUPLEX)
    pin_t tx_pin = SERIAL_USART_TX_PIN;
    pin_t rx_pin = SERIAL_USART_RX_PIN;
#else
    pin_t tx_pin = SERIAL_USART_TX_PIN;
    pin_t rx_pin = SERIAL_USART_TX_PIN;
#endif

    pio_init(tx_pin, rx_pin);
}
