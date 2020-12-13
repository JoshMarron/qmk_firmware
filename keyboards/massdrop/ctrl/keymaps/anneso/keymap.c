#include QMK_KEYBOARD_H

#include "keymap.h"

#include <sendstring_uk.h>

enum ctrl_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
    E_ACUTE,
    E_GRAVE,
    E_HAT,
    A_GRAVE,
    A_HAT,
    I_TREMA,
    U_GRAVE,
    U_HAT,
    O_HAT,
    PI_MAC
};

#define GITADDSTR "gau"
#define GCMSGSTR "gcmsg \"\""
#define GSTSTR "git status"
#define GNBRNCHSTR "git checkout -b "
#define GDREMSTR "git remote remove "
#define GAREMSTR "git remote add "

enum layout_names {
    KEY_LAYER = 0,
    ACCENT_LAYER_1,
    ACCENT_LAYER_2,
    ACCENT_LAYER_3
};

static const int _AL1 = ACCENT_LAYER_1;
static const int _AL2 = ACCENT_LAYER_2;
static const int _AL3 = ACCENT_LAYER_3;

static bool leds_off = 0;
static bool caps_on = 0;

keymap_config_t keymap_config;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [KEY_LAYER] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,             KC_PSCR, KC_SLCK, KC_PAUS, \
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,   KC_INS,  KC_HOME, KC_PGUP, \
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,   KC_DEL,  KC_END,  KC_PGDN, \
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, \
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                              KC_UP, \
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             MO(_AL1),MO(_AL2),MO(_AL3),  KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    [ACCENT_LAYER_1] = LAYOUT(
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_RMOD, RGB_VAD, RGB_MOD, _______, _______, _______, _______, _______,            KC_MUTE, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_MPLY, KC_MSTP, KC_VOLU, \
        _______, _______, _______, E_ACUTE, _______, _______, _______, U_GRAVE, I_TREMA, _______, _______, _______, _______, _______,   KC_MPRV, KC_MNXT, KC_VOLD, \
        _______, A_GRAVE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, MD_BOOT, NK_TOGG, _______, _______, _______, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
    ),
    [ACCENT_LAYER_2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, _______, _______, E_GRAVE, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
    ),
    [ACCENT_LAYER_3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            KC_MUTE, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_MPLY, KC_MSTP, KC_VOLU, \
        _______, _______, _______, E_HAT,   _______, _______, _______, U_HAT,   _______, O_HAT,   PI_MAC,  _______, _______, _______,   KC_MPRV, KC_MNXT, KC_VOLD, \
        _______, A_HAT,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
    ),
};

#define NUM_FRONT_KEYS 88
#define NUM_BORDER_KEYS 32
#define BORDER_OFFSET 87

#define YELL {237, 197, 66}
#define LYELL {80, 80, 0}
#define BLU  {24, 83, 201}
#define CYAN {0, 80, 80}
#define GREY {131, 140, 134}
#define LBLU {153, 238, 255}
#define WHITE {50, 50, 50}
#define RED {255, 0, 0}
#define PINK {255, 102, 255}
#define DGREEN {0, 179, 60}
#define PURPLE {131, 64, 207}
//#define PANGRN {85, 231, 215}
#define PANGRN DGREEN
//#define PANPNK {241, 178, 220}
#define PANPNK {204, 149, 186}

#ifdef _______
#undef _______
#define _______ {0, 0, 0}
#endif

const uint8_t PROGMEM keyledmap[][NUM_FRONT_KEYS][3] = {
    [KEY_LAYER] = {
        RED,    WHITE,   WHITE,   WHITE,   WHITE,   WHITE,     WHITE,     WHITE,     WHITE,     WHITE,   WHITE,   WHITE,   WHITE,              WHITE,     WHITE,     WHITE,
        WHITE,   WHITE,   WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE,       WHITE,     WHITE,     WHITE,
        WHITE,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,     WHITE,     WHITE,     WHITE,
        WHITE,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   RED,
        WHITE,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,                                  WHITE,
        WHITE,     WHITE,     WHITE,                       WHITE,                              WHITE,     WHITE,     WHITE,     WHITE,                WHITE,    WHITE,    WHITE
    },
    [ACCENT_LAYER_1] = {
        RED,    WHITE,   WHITE,   WHITE,   WHITE,   WHITE,     WHITE,     WHITE,     WHITE,     WHITE,   WHITE,   WHITE,   WHITE,              WHITE,     WHITE,     WHITE,
        WHITE,   WHITE,   WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE,       WHITE,     WHITE,     WHITE,
        WHITE,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,     WHITE,     WHITE,     WHITE,
        WHITE,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   RED,
        WHITE,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,                                  WHITE,
        WHITE,     WHITE,     WHITE,                       WHITE,                              WHITE,     WHITE,     WHITE,     WHITE,                WHITE,    WHITE,    WHITE
    },
    [ACCENT_LAYER_2] = {
        RED,    WHITE,   WHITE,   WHITE,   WHITE,   WHITE,     WHITE,     WHITE,     WHITE,     WHITE,   WHITE,   WHITE,   WHITE,              WHITE,     WHITE,     WHITE,
        WHITE,   WHITE,   WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE,       WHITE,     WHITE,     WHITE,
        WHITE,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,     WHITE,     WHITE,     WHITE,
        WHITE,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   RED,
        WHITE,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,                                  WHITE,
        WHITE,     WHITE,     WHITE,                       WHITE,                              WHITE,     WHITE,     WHITE,     WHITE,                WHITE,    WHITE,    WHITE
    },
    [ACCENT_LAYER_3] = {
        RED,    WHITE,   WHITE,   WHITE,   WHITE,   WHITE,     WHITE,     WHITE,     WHITE,     WHITE,   WHITE,   WHITE,   WHITE,              WHITE,     WHITE,     WHITE,
        WHITE,   WHITE,   WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE,       WHITE,     WHITE,     WHITE,
        WHITE,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,     WHITE,     WHITE,     WHITE,
        WHITE,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   RED,
        WHITE,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,                                  WHITE,
        WHITE,     WHITE,     WHITE,                       WHITE,                              WHITE,     WHITE,     WHITE,     WHITE,                WHITE,    WHITE,    WHITE
    },
};

#undef WHITE
#define WHITE {255, 255, 255}

const uint8_t PROGMEM borderledmap[][NUM_BORDER_KEYS][3] = {
    [KEY_LAYER] = {
        WHITE,    WHITE,    WHITE,    WHITE,     WHITE,     WHITE,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,     WHITE,     WHITE, // BOTTOM ROW, RIGHT TO LEFT
        WHITE,     WHITE,     WHITE,   WHITE, // LEFT SIDE, going upwards
        WHITE,    WHITE,   WHITE,   WHITE,   WHITE,     WHITE,     WHITE,     WHITE,   WHITE,   WHITE,     WHITE,     WHITE, // TOP ROW, LEFT TO RIGHT
        WHITE,     WHITE,     WHITE, // RIGHT SIDE, going down
    },
    [ACCENT_LAYER_1] = {
        WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE, // BOTTOM ROW, RIGHT TO LEFT
        WHITE,     WHITE,     WHITE,   WHITE, // LEFT SIDE, going upwards
        WHITE,    WHITE,   WHITE,   WHITE,   WHITE,     WHITE,     WHITE,     WHITE,   WHITE,   WHITE,     WHITE,     WHITE, // TOP ROW, LEFT TO RIGHT
        WHITE,     WHITE,     WHITE, // RIGHT SIDE, going down
    },
    [ACCENT_LAYER_2] = {
        WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE, // BOTTOM ROW, RIGHT TO LEFT
        WHITE,     WHITE,     WHITE,   WHITE, // LEFT SIDE, going upwards
        WHITE,    WHITE,   WHITE,   WHITE,   WHITE,     WHITE,     WHITE,     WHITE,   WHITE,   WHITE,     WHITE,     WHITE, // TOP ROW, LEFT TO RIGHT
        WHITE,     WHITE,     WHITE, // RIGHT SIDE, going down
    },
    [ACCENT_LAYER_3] = {
        WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE,  WHITE, // BOTTOM ROW, RIGHT TO LEFT
        WHITE,     WHITE,     WHITE,   WHITE, // LEFT SIDE, going upwards
        WHITE,    WHITE,   WHITE,   WHITE,   WHITE,     WHITE,     WHITE,     WHITE,   WHITE,   WHITE,     WHITE,     WHITE, // TOP ROW, LEFT TO RIGHT
        WHITE,     WHITE,     WHITE, // RIGHT SIDE, going down
    },
};


#ifdef _______
#undef _______
#define _______ KC_TRNS
#endif

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
    rgb_matrix_enable();
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};

void rgb_matrix_indicators_user(void)
{
    if (leds_off)
    {
        rgb_matrix_set_color_all(0, 0, 0);
        return;
    }
    int layer = get_highest_layer(layer_state);
    for (int i = 0; i < NUM_FRONT_KEYS; ++i)
    {
        uint8_t r = pgm_read_byte(&keyledmap[layer][i][0]);
        uint8_t g = pgm_read_byte(&keyledmap[layer][i][1]);
        uint8_t b = pgm_read_byte(&keyledmap[layer][i][2]);
        if (caps_on && i == 50)
        {
            r = 255;
            g = 0;
            b = 0;
        }
        rgb_matrix_set_color(i, r, g, b);
    }

    for (int i = 0; i < NUM_BORDER_KEYS; ++i)
    {
        uint8_t r = 0; uint8_t g = 0; uint8_t b = 0;
        r = pgm_read_byte(&borderledmap[layer][i][0]);
        g = pgm_read_byte(&borderledmap[layer][i][1]);
        b = pgm_read_byte(&borderledmap[layer][i][2]);
        rgb_matrix_set_color(i + BORDER_OFFSET, r, g, b);
    }
};

#define MODS_SHIFT  (get_mods() & MOD_MASK_SHIFT)
#define MODS_CTRL   (get_mods() & MOD_MASK_CTRL)
#define MODS_ALT    (get_mods() & MOD_MASK_ALT)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint32_t key_timer;

    switch (keycode) {
        case KC_CAPS:
            // Intercept CAPS lock
            if (record->event.pressed)
            {
                caps_on = caps_on ? 0 : 1;
            }
            return true;
        case U_T_AUTO:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_extra_manual, "USB extra port manual mode");
            }
            return false;
        case U_T_AGCR:
            if (record->event.pressed && MODS_SHIFT && MODS_CTRL) {
                TOGGLE_FLAG_AND_PRINT(usb_gcr_auto, "USB GCR auto mode");
            }
            return false;
        case DBG_TOG:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_enable, "Debug mode");
            }
            return false;
        case DBG_MTRX:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_matrix, "Debug matrix");
            }
            return false;
        case DBG_KBD:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_keyboard, "Debug keyboard");
            }
            return false;
        case DBG_MOU:
            if (record->event.pressed) {
                TOGGLE_FLAG_AND_PRINT(debug_mouse, "Debug mouse");
            }
            return false;
        case MD_BOOT:
            if (record->event.pressed) {
                key_timer = timer_read32();
            } else {
                if (timer_elapsed32(key_timer) >= 500) {
                    reset_keyboard();
                }
            }
            return false;
        case RGB_TOG:
            if (record->event.pressed) {
              leds_off = leds_off ? 0 : 1;
              switch (rgb_matrix_get_flags()) {
                case LED_FLAG_ALL: {
                    rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
                    rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                    rgb_matrix_set_color_all(0, 0, 0);
                  }
                  break;
                case LED_FLAG_UNDERGLOW: {
                    rgb_matrix_set_flags(LED_FLAG_NONE);
                    rgb_matrix_disable_noeeprom();
                  }
                  break;
                default: {
                    rgb_matrix_set_flags(LED_FLAG_ALL);
                    rgb_matrix_enable_noeeprom();
                  }
                  break;
              }
            }
            return false;
        case E_ACUTE:
            if (record->event.pressed)
            {
                SEND_STRING(SS_RALT("`") "e");
            }
            return true;
        case E_GRAVE:
            if (record->event.pressed)
            {
                SEND_STRING("`e");
            }
            return true;
        case E_HAT:
            if (record->event.pressed)
            {
                SEND_STRING(SS_RALT("6") "e");
            }
            return true;
        case A_GRAVE:
            if (record->event.pressed)
            {
                SEND_STRING("`a");
            }
            return true;
        case A_HAT:
            if (record->event.pressed)
            {
                SEND_STRING(SS_RALT("6") "a");
            }
            return true;
        case I_TREMA:
            if (record->event.pressed)
            {
                SEND_STRING(SS_RALT("2") "i");
            }
            return true;
        case U_GRAVE:
            if (record->event.pressed)
            {
                SEND_STRING("`u");
            }
            return true;
        case U_HAT:
            if (record->event.pressed)
            {
                SEND_STRING(SS_RALT("6") "u");
            }
            return true;
        case O_HAT:
            if (record->event.pressed)
            {
                SEND_STRING(SS_RALT("6") "o");
            }
            return true;
        case PI_MAC:
            if (record->event.pressed)
            {
                SEND_STRING("Patient Involvement");
            }
            return true;
        default:
            return true; //Process all other keycodes normally
    }
}
