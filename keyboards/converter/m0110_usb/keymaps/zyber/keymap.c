// Copyright 2022 ZyBeR (@ZyberSE)
// SPDX-License-Identifier: GPL-2.0

#include "zyber.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* Default:
	 * M0110                                                       M0120
	 * ,---------------------------------------------------------. ,---------------.
	 * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs| |Nlk|  =|  /|  *|
	 * |---------------------------------------------------------| |---------------|
	 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  Å|  ¨|Ent| |  7|  8|  9|  -|
	 * |------------------------------------------------------| e| |---------------|
	 * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  Ö|  Ä|  '| r| |  4|  5|  6|  +|
	 * |---------------------------------------------------------| |---------------|
	 * |Shft|  §|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|  -|Shft| |  1|  2|  3|   |
	 * `---------------------------------------------------------' |-----------|Ent|
	 *      |Opt|Mac |            Space            |Fn  |Opt|      |      0|  .|   |
	 *      `-----------------------------------------------'      `---------------'
	 * M0110A
	 * ,---------------------------------------------------------. ,---------------.
	 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs| |Nlk|  =|  /|  *|
	 * |---------------------------------------------------------| |---------------|
	 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   | |  7|  8|  9|  -|
	 * |-----------------------------------------------------'   | |---------------|
	 * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return| |  4|  5|  6|  +|
	 * |---------------------------------------------------------| |---------------|
	 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shft|Up | |  1|  2|  3|   |
	 * |---------------------------------------------------------| |-----------|Ent|
	 * |Opt  |Mac    |         Space             |  \|Lft|Rgt|Dn | |      0|  .|   |
	 * `---------------------------------------------------------' `---------------'
	 */

	[0] = LAYOUT_iso(
	       KC_GESC,   KC_1,    KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,    KC_0,             KC_MINS, KC_EQL,  KC_BSPC,     KC_NLCK, KC_EQL, KC_PSLS, KC_PAST, \
	       KC_TAB,    KC_Q,    KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,    KC_P,             KC_LBRC, KC_RBRC, KC_ENT,      KC_P7,   KC_P8,  KC_P9,   KC_PMNS, \
	       CTRL_C_UP, KC_A,    KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    KC_SCLN,          KC_QUOT, KC_NUHS,              KC_P4,   KC_P5,  KC_P6,   KC_PPLS, \
	       KC_LSFT,   KC_NUBS, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH,                                KC_P1,   KC_P2,  KC_P3,   KC_PENT, \
	               KC_LALT,   KC_LGUI,                        KC_SPC,                        MO(1),                                LT(1, KC_BSLASH), KC_DOWN),


	/* Cursor Layer:
	 * M0110                                                       M0120
	 * ,---------------------------------------------------------. ,---------------.
	 * |RES| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delet| |Nlk|  =|  /|  *|
	 * |---------------------------------------------------------| |---------------|
	 * |Tab  |Hom| Up|PgU|Rst|   |   |   |Psc|Slk|Pau|Up |INS|   | |  7|  8|  9|  -|
	 * |---------------------------------------------------------| |---------------|
	 * |Ctrl  |Lef|Dow|Rig|   |   |   |   |Hom|PgU|Lef|Rig|Return| |  4|  5|  6|  +|
	 * |---------------------------------------------------------| |---------------|
	 * |Shift   |End|   |PgD|   |   |   |   |End|PgD|Dow|Shift   | |  1|  2|  3|   |
	 * `---------------------------------------------------------' |-----------|Ent|
	 *      |Opt|Mac |         Space               |Fn  |Opt|      |      0|  .|   |
	 *      `-----------------------------------------------'      `---------------'
	 * M0110A
	 * ,---------------------------------------------------------. ,---------------.
	 * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delet| |Nlk|  =|  /|  *|
	 * |---------------------------------------------------------| |---------------|
	 * |Tab  |Hom| Up|PgU|   |   |   |   |Psc|Slk|Pau|Up |INS|   | |  7|  8|  9|  -|
	 * |-----------------------------------------------------'   | |---------------|
	 * |Caps  |Lef|Dow|Rig|   |   |   |   |Hom|PgU|Lef|Rig|Return| |  4|  5|  6|  +|
	 * |---------------------------------------------------------| |---------------|
	 * |Ctrl    |End|   |PgD|   |   |   |   |End|PgD|Dow|Shft|PgU| |  1|  2|  3|   |
	 * |---------------------------------------------------------| |-----------|Ent|
	 * |Opt  |Mac    |         Space             |  \|Hom|End|PgD| |      0|  .|   |
	 * `---------------------------------------------------------' `---------------'
	 */

	[1] = LAYOUT_iso(
		QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,      _______, _______, _______, _______, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______,              _______, _______, _______, _______, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT,                       _______, _______, _______, _______, \
		_______, _______,                   _______,                      _______,                                                        _______, _______),
};
