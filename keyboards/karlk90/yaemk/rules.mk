# Shared configs
LTO_ENABLE = yes
EXTRAFLAGS += -O2

# YAEMK source files
SRC = led_config.c custom_color.c

# QMK features
CONSOLE_ENABLE                     = no
CAPS_WORD_ENABLE                   = yes
DEBOUNCE_TYPE                      = asym_eager_defer_pk
EEPROM_DRIVER                      = i2c
ENCODER_ENABLE                     = yes
EXTRAKEY_ENABLE                    = yes
MOUSEKEY_ENABLE                    = yes
NKRO_ENABLE                        = yes
OLED_ENABLE                        = yes
OLED_DRIVER                        = SSD1306
RGB_MATRIX_ENABLE                  = yes
RGB_MATRIX_DRIVER                  = WS2812
WS2812_DRIVER                      = pwm
SERIAL_DRIVER                      = usart
SPLIT_KEYBOARD                     = yes
