// Copyright 2022 Diego Palacios (@diepala)
// SPDX-License-Identifier: GPL-2.0

#include QMK_KEYBOARD_H

enum Layers {
    BASE = 0,
    MEDIA = 1,
    NAV = 2,
    MOUSE = 3,
    SYM = 4,
    NUM = 5,
    FN = 6,
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │Tab│ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │Bsp│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Ctl│ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ; │ ' │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Sft│ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ / │Sft│
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │GUI├───┐           ┌───┤Alt│
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤Bsp│   │Ent├───┘
      *                       └───┘   └───┘
      */
 [BASE] = LAYOUT_split_3x6_3( \
    XXXXXXX        , KC_Q          , KC_W          , KC_E          , KC_R          , KC_T          ,                                 KC_Y          , KC_U          , KC_I          , KC_O          , KC_P,            XXXXXXX      ,\
    XXXXXXX        , LGUI_T(KC_A)  , LALT_T(KC_S)  , LCTL_T(KC_D)  , LSFT_T(KC_F)  , KC_G          ,                                 KC_H          , LSFT_T(KC_J)  , LCTL_T(KC_K)  , LALT_T(KC_L)  , LGUI_T(KC_SCLN), XXXXXXX      ,\
    XXXXXXX        , KC_Z          , KC_X          , KC_C          , KC_V          , KC_B          ,                                 KC_N          , KC_M          , KC_COMM       , KC_DOT        , KC_SLSH,         XXXXXXX      ,\
                                                                 LT(MEDIA, KC_ESC) , LT(NAV, KC_SPC) , LT(MOUSE, KC_TAB) , LT(SYM, KC_ENT) , LT(NUM, KC_BSPC) , LT(FN, KC_DEL) \
 ),
 [MEDIA] = LAYOUT_split_3x6_3( \
   XXXXXXX         , _______       , _______       , _______       , _______       , _______       ,                                 _______       , _______       , _______       , _______       , _______       , XXXXXXX       ,\
   XXXXXXX         , KC_LGUI       , KC_LALT       , KC_LCTL       , KC_LSFT       , _______       ,                                 KC_MPRV       , KC_VOLD       , KC_VOLU       , KC_MNXT       , _______       , XXXXXXX       ,\
   XXXXXXX         , _______       , _______       , _______       , _______       , _______       ,                                 _______       , _______       , _______       , _______       , _______       , XXXXXXX       ,\
                                                                     _______       , _______       , _______       , KC_MSTP       , KC_MPLY       , KC_MUTE \
 ),
 [NAV] = LAYOUT_split_3x6_3( \
   XXXXXXX         , _______       , _______       , _______       , _______       , _______       ,                                 C(KC_Y)       , C(KC_V)       , C(KC_C)       , C(KC_X)       , C(KC_Z)       , XXXXXXX       ,\
   XXXXXXX         , KC_LGUI       , KC_LALT       , KC_LCTL       , KC_LSFT       , _______       ,                                 KC_LEFT       , KC_DOWN       , KC_UP         , KC_RIGHT      , KC_CAPS       , XXXXXXX       ,\
   XXXXXXX         , _______       , _______       , _______       , _______       , _______       ,                                 KC_HOME       , KC_PGDN       , KC_PGUP       , KC_END        , KC_INS        , XXXXXXX       ,\
                                                                   , _______       , _______       , _______       , KC_ENT        , KC_BSPC       , KC_DEL \
 ),
 [MOUSE] = LAYOUT_split_3x6_3( \
   XXXXXXX         , _______       , _______       , _______       , _______       , _______       ,                                 C(KC_Y)       , C(KC_V)       , C(KC_C)       , C(KC_X)       , C(KC_Z)       , XXXXXXX       ,\
   XXXXXXX         , KC_LGUI       , KC_LALT       , KC_LCTL       , KC_LSFT       , _______       ,                                 KC_MS_L       , KC_MS_D       , KC_MS_U       , KC_MS_R       , _______       , XXXXXXX       ,\
   XXXXXXX         , _______       , _______       , _______       , _______       , _______       ,                                 KC_WH_L       , KC_WH_D       , KC_WH_U       , KC_WH_R       , _______       , XXXXXXX       ,\
                                                                   , _______       , _______       , _______       , KC_BTN1       , KC_BTN3       , KC_BTN2 \
 ),
 [SYM] = LAYOUT_split_3x6_3( \
   XXXXXXX         , KC_LCBR       , KC_AMPR       , KC_ASTR       , KC_LPRN       , KC_RCBR       ,                                 _______       , _______       , _______       , _______       , _______       , XXXXXXX       ,\
   XXXXXXX         , S(KC_QUOT)    , KC_DLR        , KC_PERC       , KC_CIRC       , KC_PLUS       ,                                 _______       , KC_LSFT       , KC_LCTL       , KC_LALT       , KC_LGUI       , XXXXXXX       ,\
   XXXXXXX         , KC_TILD       , KC_EXLM       , KC_AT         , KC_HASH       , KC_PIPE       ,                                 _______       , _______       , _______       , _______       , _______       , XXXXXXX       ,\
                                                                   , KC_LPRN       , KC_RPRN       , KC_UNDS       , _______       , _______       , _______ \
 ),
 [NUM] = LAYOUT_split_3x6_3( \
   XXXXXXX         , KC_LBRC       , KC_7          , KC_8          , KC_9          , KC_RBRC       ,                                 _______       , _______       , _______       , _______       , _______       , XXXXXXX       ,\
   XXXXXXX         , KC_QUOT       , KC_4          , KC_5          , KC_6          , KC_EQL        ,                                 _______       , KC_LSFT       , KC_LCTL       , KC_LALT       , KC_LGUI       , XXXXXXX       ,\
   XXXXXXX         , KC_GRV        , KC_1          , KC_2          , KC_3          , KC_BSLS       ,                                 _______       , _______       , _______       , _______       , _______       , XXXXXXX       ,\
                                                                   , KC_DOT        , KC_0          , KC_MINS       , _______       , _______       , _______ \
 ),
 [FN] = LAYOUT_split_3x6_3( \
   XXXXXXX         , KC_F12        , KC_F7         , KC_F8         , KC_F9         , KC_PSCR       ,                                 _______       , _______       , _______       , _______       , _______       , XXXXXXX       ,\
   XXXXXXX         , KC_F11        , KC_F4         , KC_F5         , KC_F6         , KC_SLCK       ,                                 _______       , KC_LSFT       , KC_LCTL       , KC_LALT       , KC_LGUI       , XXXXXXX       ,\
   XXXXXXX         , KC_F10        , KC_F1         , KC_F2         , KC_F3         , KC_PAUS       ,                                 _______       , _______       , _______       , _______       , _______       , XXXXXXX       ,\
                                                                   , KC_APP        , KC_SPC        , KC_TAB        , _______       , _______       , _______ \
 ),
};

// clang-format on

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LSFT_T(KC_F):
        case LSFT_T(KC_J):
            return TAPPING_TERM - 50;
        case LGUI_T(KC_A):
        case LGUI_T(KC_SCLN):
            return TAPPING_TERM + 50;
        default:
            return TAPPING_TERM;
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


