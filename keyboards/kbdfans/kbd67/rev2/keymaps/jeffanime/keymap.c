/* Copyright 2018 'mechmerlin'
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  GITADDU = SAFE_RANGE,
  GCMSG,
  GST,
  GNBRNCH,
  GAREM,
  GDREM
};

enum unicode_names {
    SHRUG,
    POOP
};

const uint32_t PROGMEM unicode_map[] = {
    [SHRUG] = 0x1F937,
    [POOP] = 0x1F4A9
};

#define HSV_PANPNK 227, 255, 204
#define HSV_PANGRN 99, 255, 179

const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_RED});
const rgblight_segment_t PROGMEM default_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_PANPNK});
const rgblight_segment_t PROGMEM second_layer[]   = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_PANGRN});

const rgblight_segment_t* const PROGMEM jeff_rgb_layers[] = RGBLIGHT_LAYERS_LIST(default_layer, second_layer, capslock_layer);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap (Base Layer) Default Layer
     * ,----------------------------------------------------------------.
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |Home|
     * |----------------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  |PgUp|
     * |----------------------------------------------------------------|
     * |Caps   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |PgDn|
     * |----------------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift | Up|End |
     * |----------------------------------------------------------------|
     * |Ctrl|Win |Alt |        Space          |Alt| FN|Ctrl|Lef|Dow|Rig |
     * `----------------------------------------------------------------'
     */
[0] = LAYOUT_65_ansi(
  KC_GRV,  KC_1,    KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_ESC, \
  KC_TAB,  KC_Q,    KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_VOLU, \
  KC_CAPS, KC_A,    KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_VOLD,  \
  KC_LSFT, KC_Z,    KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,            KC_MUTE,  \
  KC_LCTL, KC_LGUI, KC_LALT,                KC_SPC,                          KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),

    /* Keymap Fn Layer
     * ,----------------------------------------------------------------.
     * |~ `|F1 |F2 |F3 |F4 |F5 |F6 |F7 |F8 |F9 |F10|F11|F12|Del    |Ins |
     * |----------------------------------------------------------------|
     * |     |   |Up |   |   |   |   |   |PSc|SLk|Pau|Up |   |     |    |
     * |----------------------------------------------------------------|
     * |      |Lef|Dow|Rig|   |   |   |   |Hom|PUp|Lef|Rig|        |    |
     * |----------------------------------------------------------------|
     * |        |   |   |   |   |   |   |   |End|PDn|Dow|      |PUp|    |
     * |----------------------------------------------------------------|
     * |    |    |    |                       |   |   |    |Hom|PDn|End |
     * `----------------------------------------------------------------'
     */
[1] = LAYOUT_65_ansi(
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11,   KC_F12,  KC_DEL,  KC_MPLY, \
  _______, _______, _______, _______, RESET,   _______, _______, UC_MOD,  KC_PSCR, KC_SLCK, X(POOP), KC_UP,   _______, _______, KC_MPRV, \
  _______, GITADDU, GST,     _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,          _______, KC_MNXT, \
  _______, _______, _______, GCMSG,   _______, GNBRNCH, _______, _______, KC_END,  KC_PGDN, KC_DOWN, _______, KC_PGUP,          KC_MPLY, \
  _______, _______, _______,                   _______,                            _______, _______, _______, KC_HOME, KC_PGDN, KC_END),

};

void keyboard_post_init_user(void) {
    rgblight_layers = jeff_rgb_layers;
    rgblight_set_layer_state(0, 1);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case GITADDU:
        if (record->event.pressed)
        {
            SEND_STRING("git add -u" SS_TAP(X_ENT));
        }
        break;
    case GCMSG:
        if (record->event.pressed)
        {
            SEND_STRING("gcmsg \"\"" SS_TAP(X_LEFT));
        }
        break;
    case GST:
        if (record->event.pressed)
        {
            SEND_STRING("git status" SS_TAP(X_ENT));
        }
        break;
    case GNBRNCH:
        if (record->event.pressed)
        {
            SEND_STRING("git checkout -b ");
        }
        break;
  }
  return true;
}

void matrix_init_user(void) {
    // rgblight_mode(1);
    // rgblight_sethsv_range(HSV_BLUE, 0, 20);
}

void matrix_scan_user(void) {

}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    return state;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(2, led_state.caps_lock);
    return true;
}

void led_set_user(uint8_t usb_led) {

}
