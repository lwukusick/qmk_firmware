#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include "printf.h"

#if defined(RGB_MATRIX_ENABLE)
extern rgb_config_t rgb_matrix_config;
#endif

enum Layers {
    _BASE = 0,
    _SYM  = 1,
    _NAV  = 2,
    _FN   = 3,
    _RGB  = 4,
};

enum Encoder {
    _ENCODER_LEFT  = 0,
    _ENCODER_RIGHT = 1,
};

// clang-format off

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( \
     KC_ESC         , KC_1          , KC_2          , KC_3          , KC_4          , KC_5          , LCTL(DE_CIRC) ,                                 KC_ESC        , KC_6          , KC_7          , KC_8          , KC_9          , KC_0          , DE_MINS       ,\
     KC_TAB         , DE_K          , DE_DOT        , DE_O          , DE_COMM       , DE_Y          , MO(_RGB)      ,                                 MO(_RGB)      , DE_V          , DE_G          , DE_C          , DE_L          , DE_SS         , DE_Z          ,\
     MO(_SYM)       , LGUI_T(DE_H)  , LALT_T(DE_A)  , LCTL_T(DE_E)  , LT(_SYM,DE_I) , DE_U          , MO(_FN)       ,                                 MO(_FN)       , DE_D          , LT(_SYM,DE_T) , RCTL_T(DE_R)  , RALT_T(DE_N)  , RGUI_T(DE_S)  , DE_F          ,\
     MO(_NAV)       , DE_X          , DE_Q          , DE_ADIA       , DE_UDIA       , DE_ODIA       , KC_BSPC       , MO(_NAV)      , MO(_NAV)      , KC_ENT        , DE_B          , DE_P          , DE_W          , DE_M          , DE_J          , MO(_NAV)      ,\
                                                      KC_NO,          KC_ESC        , LSFT_T(KC_SPC), KC_BSPC       , MO(_NAV)      , MO(_NAV)      , KC_ENT        , RSFT_T(KC_SPC), KC_RALT       , KC_NO \
  ),
   [_SYM] = LAYOUT( \
    _______         , _______       , _______       , _______       , _______       , _______       , _______       ,                                 _______       , _______       , _______       , _______       , _______       , _______       , _______       ,\
    _______         , _______       , DE_UNDS       , DE_LBRC       , DE_RBRC       , DE_CIRC       , _______       ,                                 _______       , DE_EXLM       , DE_LABK       , DE_RABK       , DE_EQL        , DE_AMPR       , _______       ,\
    _______         , DE_BSLS       , DE_SLSH       , DE_LCBR       , DE_RCBR       , DE_ASTR       , _______       ,                                 _______       , DE_QUES       , DE_LPRN       , DE_RPRN       , DE_MINS       , DE_COLN       , DE_AT         ,\
    _______         , DE_HASH       , DE_DLR        , DE_PIPE       , DE_TILD       , DE_GRV        , _______       , _______       , _______       , _______       , DE_PLUS       , DE_PERC       , DE_DQUO       , DE_QUOT       , DE_SCLN       , _______       ,\
                                                      _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______ \
  ),
   [_NAV] = LAYOUT( \
    _______         , _______       , _______       , _______       , _______       , _______       , _______       ,                                 _______       , _______       , _______       , _______       , _______       , DE_ASTR       , DE_SLSH       ,\
    _______         , KC_PGUP       , KC_BSPC       , KC_UP         , KC_DELETE     , KC_PGDN       , _______       ,                                 _______       , _______       , KC_7          , KC_8          , KC_9          , DE_PLUS       , DE_MINS       ,\
    _______         , KC_HOME       , KC_LEFT       , KC_DOWN       , KC_RIGHT      , KC_END        , _______       ,                                 _______       , _______       , LT(_SYM,KC_4) , RCTL_T(KC_5)  , RALT_T(KC_6)  ,RGUI_T(DE_COMM), DE_DOT        ,\
    _______         , KC_ESC        , KC_TAB        , _______       , KC_ENT        , _______       , _______       , _______       , _______       , _______       , _______       , KC_1          , KC_2          , KC_3          , DE_SCLN       , _______       ,\
                                                      _______       , _______       , _______       , _______       , _______       , _______       , _______       , KC_0          , _______       , _______ \
  ),
   [_FN] = LAYOUT( \
    _______         , _______       , KC_ACL0       , KC_ACL1       , KC_ACL2       , RESET         , _______       ,                                 _______       , RESET         , KC_F10        , KC_F11        , KC_F12        , _______       , _______       ,\
    _______         , _______       , KC_BTN1       , KC_MS_U       , KC_BTN2       , KC_PSCR       , _______       ,                                 _______       , _______       , KC_F7         , KC_F8         , KC_F9         , _______       , _______       ,\
    _______         , _______       , KC_MS_L       , KC_MS_D       , KC_MS_R       , _______       , _______       ,                                 _______       , _______       , KC_F4         , KC_F5         , KC_F6         , _______       , _______       ,\
    _______         , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , KC_F1         , KC_F2         , KC_F3         , _______       , _______       ,\
                                                      KC_MPLY       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , KC_AUDIO_MUTE \
  ),
  [_RGB] = LAYOUT( \
    _______         , _______       , _______       , _______       , _______       , _______       , _______       ,                                 _______       , _______       , RGB_TOG       , RGB_M_SW      , _______       , _______       , _______       ,\
    _______         , _______       , _______       , _______       , _______       , _______       , _______       ,                                 _______       , _______       , RGB_HUI       , RGB_HUD       , RGB_SAI       , RGB_SAD       , _______       ,\
    _______         , _______       , _______       , _______       , _______       , _______       , _______       ,                                 _______       , _______       , RGB_MOD       , RGB_RMOD      , RGB_SPI       , RGB_SPD       , _______       ,\
    _______         , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , RGB_VAI       , RGB_VAD       , _______       , _______       , _______       ,\
                                                      _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______       , _______ \
  )
};

// clang-format on

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case KC_A ... KC_Z:
        case DE_ADIA:
        case DE_UDIA:
        case DE_ODIA:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;

        // Keycodes that continue Caps Word, without shifting.
        case KC_1 ... KC_0:
        case KC_BSPC:
        case KC_DEL:
        case DE_UNDS:
        case DE_MINS:
            return true;

        default:
            return false;  // Deactivate Caps Word.
    }
}

#if defined(IGNORE_MOD_TAP_INTERRUPT_PER_KEY)
bool get_ignore_mod_tap_interrupt(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_SPC):
            return false;
        case RSFT_T(KC_SPC):
            return false;
        default:
            return true;
    }
}
#endif

#if defined(HOLD_ON_OTHER_KEY_PRESS_PER_KEY)
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_SPC):
            return true;
        case RSFT_T(KC_SPC):
            return true;
        default:
            return false;
    }
}
#endif

#if defined(ENCODER_ENABLE)
bool encoder_update_user(uint8_t index, bool clockwise) {
    layer_state_t current_state = get_highest_layer(layer_state);

    if (index == _ENCODER_LEFT) {
        if (clockwise) {
            switch (current_state) {
                case _BASE:
                default:
                    tap_code(KC_MS_WH_DOWN);
                    break;
                case _NAV:
                    tap_code(KC_MS_WH_RIGHT);
                    break;
                case _FN:
                    tap_code_delay(KC_AUDIO_VOL_UP, 10);
                    break;
                case _RGB:
                    tap_code(KC_PGUP);
                    break;
            }
        } else {
            switch (current_state) {
                case _BASE:
                default:
                    tap_code(KC_MS_WH_UP);
                    break;
                case _NAV:
                    tap_code(KC_MS_WH_LEFT);
                    break;
                case _FN:
                    tap_code_delay(KC_AUDIO_VOL_DOWN, 10);
                    break;
                case _RGB:
                    tap_code(KC_PGDN);
                    break;
            }
        }
    } else if (index == _ENCODER_RIGHT) {
        if (clockwise) {
            switch (current_state) {
                case _BASE:
                default:
                    tap_code(KC_MS_WH_DOWN);
                    break;
                case _NAV:
                    tap_code(KC_MS_WH_RIGHT);
                    break;
                case _FN:
                    tap_code_delay(KC_MEDIA_NEXT_TRACK, 10);
                    break;
                case _RGB:
                    tap_code(KC_PGUP);
                    break;
            }
        } else {
            switch (current_state) {
                case _BASE:
                default:
                    tap_code(KC_MS_WH_UP);
                    break;
                case _NAV:
                    tap_code(KC_MS_WH_LEFT);
                    break;
                case _FN:
                    tap_code_delay(KC_MEDIA_PREV_TRACK, 10);
                    break;
                case _RGB:
                    tap_code(KC_PGDN);
                    break;
            }
        }
    }

    return false;
}
#endif

#if defined(OLED_ENABLE)

#    define w_val(str, val)                         \
        snprintf(buffer, sizeof(buffer), str, val); \
        oled_write_ln(buffer, false)

void render_display(void) {
    static layer_state_t last_state    = ~0;
    layer_state_t        current_state = get_highest_layer(layer_state);

    if (last_state <= _NAV && current_state <= _NAV) {
        // Don't do anything if we are on the default layers
        return;
    } else if (last_state != current_state) {
        oled_clear();
        last_state = current_state;
    } else if (current_state != _RGB && current_state != _FN) {
        return;
    }

    static char buffer[25];
    switch (current_state) {
        case _FN:
            oled_write_ln("Function\n", false);
#    if defined(DEBUG_MATRIX_SCAN_RATE)
            oled_write_ln("Scan Freq:", false);
            w_val("%05ld", get_matrix_scan_rate());
#    endif
            break;
        case _RGB:
#    if defined(RGB_MATRIX_ENABLE)
            oled_write_ln("RGB\n", false);
            w_val("En:   %03d\n", rgb_matrix_config.enable);
            w_val("Mode: %03d\n", rgb_matrix_config.mode);
            w_val("Hue:  %03d\n", rgb_matrix_config.hsv.h);
            w_val("Sat:  %03d\n", rgb_matrix_config.hsv.s);
            w_val("Bri:  %03d\n", rgb_matrix_config.hsv.v);
            w_val("Spd:  %03d\n", rgb_matrix_config.speed);
            break;
#    endif
        default:
            if (is_keyboard_master()) {
                oled_write_ln("\x7K.O,Y\x7", false);
            } else {
                oled_write_ln("K.O,Y", false);
            }
            break;
    }
}
#endif
