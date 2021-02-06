#include QMK_KEYBOARD_H

#define HSV_PANGRN 99, 255, 179
#define HSV_PANPNK 227, 255, 204

const rgblight_segment_t PROGMEM default_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_PANGRN});
const rgblight_segment_t PROGMEM movement_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_RED});
const rgblight_segment_t PROGMEM modifier_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 20, HSV_PANPNK});

rgblight_segment_t const* const PROGMEM jeff_rgb_layers[] = RGBLIGHT_LAYERS_LIST(default_layer, movement_layer, modifier_layer);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        TG(1),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_RSFT,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,  KC_SPC,  KC_SPC,           MO(2),   MO(2),   KC_RGUI, XXXXXXX, KC_RCTL
    ),

    LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______,                   _______, _______, _______,          _______, _______, _______, _______, _______
    ),

    LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_DEL,
        _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______, _______, _______, _______, KC_VOLU,
        _______, _______, _______, _______, _______, _______, BL_INC,  _______, _______, _______, _______, _______,          KC_VOLD,
        _______, _______, _______, _______, BL_DEC,  BL_TOGG, RESET,   BL_STEP, _______, _______, _______, _______, _______, KC_MPLY,
        _______, _______, _______,                   _______, _______, _______,          _______, _______, _______, _______, _______
    )
};

void keyboard_post_init_user(void) {
    rgblight_layers = jeff_rgb_layers;
    rgblight_set_layer_state(0, 1);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    return state;
}
