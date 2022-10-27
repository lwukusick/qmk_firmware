MCU        = GD32VF103
BOARD      = SIPEED_LONGAN_NANO
BOOTLOADER = gd32v-dfu
OPT_DEFS   += -DOVERCLOCK_120MHZ

# This setting is mandatory with VIA on GD32VF103/RISC-V,
# because the MCU has a limited amount of USB endpoints.
KEYBOARD_SHARED_EP = yes
