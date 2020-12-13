#include QMK_KEYBOARD_H

#include "keymap.h"

enum ctrl_keycodes {
    U_T_AUTO = SAFE_RANGE, //USB Extra Port Toggle Auto Detect / Always Active
    U_T_AGCR,              //USB Toggle Automatic GCR control
    DBG_TOG,               //DEBUG Toggle On / Off
    DBG_MTRX,              //DEBUG Toggle Matrix Prints
    DBG_KBD,               //DEBUG Toggle Keyboard Prints
    DBG_MOU,               //DEBUG Toggle Mouse Prints
    MD_BOOT,               //Restart into bootloader after hold timeout
    GITADDU,               // git add -u
    GCMSG,                 // git commit -m ""
    GST,
    GNBRNCH,
    GDREM,
    GAREM
};

#define GITADDSTR "gau"
#define GCMSGSTR "gcmsg \"\""
#define GSTSTR "git status"
#define GNBRNCHSTR "git checkout -b "
#define GDREMSTR "git remote remove "
#define GAREMSTR "git remote add "

static const int _FL = FUNC_LAYER;
static const int _ML = MACRO_LAYER;

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
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_RALT, MO(_FL), MO(_ML),  KC_RCTL,            KC_LEFT, KC_DOWN, KC_RGHT \
    ),
    [FUNC_LAYER] = LAYOUT(
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_RMOD, RGB_VAD, RGB_MOD, _______, _______, _______, _______, _______,            KC_MUTE, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   KC_MPLY, KC_MSTP, KC_VOLU, \
        _______, _______, KC_UP,   _______, _______, RGB_SAI, _______, U_T_AUTO,U_T_AGCR,_______, _______, _______, _______, _______,   KC_MPRV, KC_MNXT, KC_VOLD, \
        _______, KC_LEFT, KC_DOWN, KC_RGHT, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______, _______, \
        _______, RGB_TOG, _______, _______, _______, MD_BOOT, NK_TOGG, _______, _______, _______, _______, _______,                              _______, \
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______ \
    ),
    [MACRO_LAYER] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, _______, _______, _______, GAREM,   _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______, \
        _______, GITADDU, GST,     GDREM,   _______, _______, _______, _______, _______, _______, _______, _______, _______, \
        _______, _______, _______, GCMSG,   _______, GNBRNCH, _______, _______, _______, _______, _______, _______,                              _______, \
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
#define WHITE {255, 255, 255}
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

#define COLORSCHEME_BREEZE 1
#define COLORSCHEME_SUSHI 2
#define COLORSCHEME_ANALOGDREAMS 3

#define COLORSCHEME_INDEX COLORSCHEME_ANALOGDREAMS

#if COLORSCHEME_INDEX == COLORSCHEME_BREEZE
const uint8_t PROGMEM keyledmap[][NUM_FRONT_KEYS][3] = {
    [KEY_LAYER] = {
        YELL,    WHITE,   WHITE,   WHITE,   WHITE,   BLU,     BLU,     BLU,     BLU,     WHITE,   WHITE,   WHITE,   WHITE,              BLU,     BLU,     BLU,
        WHITE,   WHITE,   WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , BLU,       BLU,     BLU,     BLU,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,     BLU,     BLU,     BLU,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   YELL,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   BLU,                                  YELL,
        BLU,     BLU,     BLU,                       WHITE,                              BLU,     BLU,     BLU,     BLU,                YELL,    YELL,    YELL
    },
    [FUNC_LAYER] = {
        YELL,    WHITE,   WHITE,   WHITE,   WHITE,   BLU,     BLU,     BLU,     BLU,     WHITE,   WHITE,   WHITE,   WHITE,              BLU,     BLU,     BLU,
        WHITE,   WHITE,   WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , BLU,       BLU,     BLU,     BLU,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,     BLU,     BLU,     BLU,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   YELL,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   BLU,                                  YELL,
        BLU,     BLU,     BLU,                       WHITE,                              BLU,     BLU,     BLU,     BLU,                YELL,    YELL,    YELL
    },
    [MACRO_LAYER] = {
        YELL,    WHITE,   WHITE,   WHITE,   WHITE,   BLU,     BLU,     BLU,     BLU,     WHITE,   WHITE,   WHITE,   WHITE,              BLU,     BLU,     BLU,
        WHITE,   WHITE,   WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , WHITE  , BLU,       BLU,     BLU,     BLU,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,     BLU,     BLU,     BLU,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   YELL,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   BLU,                                  YELL,
        BLU,     BLU,     BLU,                       WHITE,                              BLU,     BLU,     BLU,     BLU,                YELL,    YELL,    YELL
    },
};
#elif COLORSCHEME_INDEX == COLORSCHEME_SUSHI
const uint8_t PROGMEM keyledmap[][NUM_FRONT_KEYS][3] = {
    [KEY_LAYER] = {
        CYAN,    WHITE,   WHITE,   WHITE,   WHITE,   LYELL,   LYELL,   LYELL,   LYELL,   WHITE,   WHITE,   WHITE,   WHITE,              CYAN,    CYAN,    CYAN,
        CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    LYELL,     BLU,     BLU,     BLU,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,     BLU,     BLU,     BLU,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   LYELL,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   LYELL,                                CYAN,
        BLU,     LYELL,   BLU,                       WHITE,                              BLU,     LYELL,   BLU,     BLU,                CYAN,    CYAN,    CYAN
    },
    [FUNC_LAYER] = {
        CYAN,    WHITE,   WHITE,   WHITE,   WHITE,   LYELL,   LYELL,   LYELL,   LYELL,   WHITE,   WHITE,   WHITE,   WHITE,              CYAN,    CYAN,    CYAN,
        CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    LYELL,     BLU,     BLU,     BLU,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,     BLU,     BLU,     BLU,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   LYELL,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   LYELL,                                CYAN,
        BLU,     LYELL,   BLU,                       WHITE,                              BLU,     LYELL,   BLU,     BLU,                CYAN,    CYAN,    CYAN
    },
    [MACRO_LAYER] = {
        CYAN,    WHITE,   WHITE,   WHITE,   WHITE,   LYELL,   LYELL,   LYELL,   LYELL,   WHITE,   WHITE,   WHITE,   WHITE,              CYAN,    CYAN,    CYAN,
        CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    LYELL,     BLU,     BLU,     BLU,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,     BLU,     BLU,     BLU,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   LYELL,
        BLU,     WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   WHITE,   LYELL,                                CYAN,
        BLU,     LYELL,   BLU,                       WHITE,                              BLU,     LYELL,   BLU,     BLU,                CYAN,    CYAN,    CYAN
    },
};
#elif COLORSCHEME_INDEX == COLORSCHEME_ANALOGDREAMS
const uint8_t PROGMEM keyledmap[][NUM_FRONT_KEYS][3] = {
    [KEY_LAYER] = {
        PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANGRN,  PANGRN,  PANGRN,  PANGRN,  PANPNK,  PANPNK,  PANPNK,  PANPNK,             PANGRN,  PANGRN,  PANGRN,
        PANGRN,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANGRN,    PANGRN,  PANGRN,  PANGRN,
        PANGRN,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,    PANGRN,  PANGRN,  PANGRN,
        PANGRN,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,
        PANGRN,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANGRN,                               PANPNK,
        PANGRN,  PANGRN,  PANGRN,                    PANPNK,                             PANGRN,  PANGRN,  PANGRN,  PANGRN,             PANPNK,  PANPNK,  PANPNK
    },
    [FUNC_LAYER] = {
        PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANGRN,  PANGRN,  PANGRN,  PANGRN,  PANPNK,  PANPNK,  PANPNK,  PANPNK,             PANGRN,  PANGRN,  PANGRN,
        PANGRN,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANGRN,    PANGRN,  PANGRN,  PANGRN,
        PANGRN,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,    PANGRN,  PANGRN,  PANGRN,
        PANGRN,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,
        PANGRN,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANGRN,                               PANPNK,
        PANGRN,  PANGRN,  PANGRN,                    PANPNK,                             PANGRN,  PANGRN,  PANGRN,  PANGRN,             PANPNK,  PANPNK,  PANPNK
    },
    [MACRO_LAYER] = {
        PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANGRN,  PANGRN,  PANGRN,  PANGRN,  PANPNK,  PANPNK,  PANPNK,  PANPNK,             PANGRN,  PANGRN,  PANGRN,
        PANGRN,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANGRN,    PANGRN,  PANGRN,  PANGRN,
        PANGRN,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,    PANGRN,  PANGRN,  PANGRN,
        PANGRN,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,
        PANGRN,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANGRN,                               PANPNK,
        PANGRN,  PANGRN,  PANGRN,                    PANPNK,                             PANGRN,  PANGRN,  PANGRN,  PANGRN,             PANPNK,  PANPNK,  PANPNK
    },
};
#endif

#if COLORSCHEME_INDEX == COLORSCHEME_SUSHI
const uint8_t PROGMEM borderledmap[][NUM_BORDER_KEYS][3] = {
    [KEY_LAYER] = {
        YELL,    YELL,    GREY,    BLU,     BLU,     BLU,     WHITE,   WHITE,   WHITE,   WHITE,   BLU,     BLU,     BLU, // BOTTOM ROW, RIGHT TO LEFT
        BLU,     BLU,     WHITE,   YELL, // LEFT SIDE, going upwards
        YELL,    WHITE,   WHITE,   WHITE,   BLU,     BLU,     BLU,     WHITE,   WHITE,   BLU,     BLU,     BLU, // TOP ROW, LEFT TO RIGHT
        BLU,     BLU,     YELL, // RIGHT SIDE, going down
    },
    [FUNC_LAYER] = {
        DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN, // BOTTOM ROW, RIGHT TO LEFT
        BLU,     BLU,     WHITE,   YELL, // LEFT SIDE, going upwards
        YELL,    WHITE,   WHITE,   WHITE,   BLU,     BLU,     BLU,     WHITE,   WHITE,   BLU,     BLU,     BLU, // TOP ROW, LEFT TO RIGHT
        BLU,     BLU,     YELL, // RIGHT SIDE, going down
    },
    [MACRO_LAYER] = {
        PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE, // BOTTOM ROW, RIGHT TO LEFT
        BLU,     BLU,     WHITE,   YELL, // LEFT SIDE, going upwards
        YELL,    WHITE,   WHITE,   WHITE,   BLU,     BLU,     BLU,     WHITE,   WHITE,   BLU,     BLU,     BLU, // TOP ROW, LEFT TO RIGHT
        BLU,     BLU,     YELL, // RIGHT SIDE, going down
    },
};
#elif COLORSCHEME_INDEX == COLORSCHEME_BREEZE
const uint8_t PROGMEM borderledmap[][NUM_BORDER_KEYS][3] = {
    [KEY_LAYER] = {
        CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,   CYAN, // BOTTOM ROW, RIGHT TO LEFT
        CYAN,    CYAN,    CYAN,    CYAN, // LEFT SIDE, going upwards
        CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN, // TOP ROW, LEFT TO RIGHT
        CYAN,    CYAN,    CYAN, // RIGHT SIDE, going down
    },
    [FUNC_LAYER] = {
        DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN, // BOTTOM ROW, RIGHT TO LEFT
        CYAN,    CYAN,    CYAN,    CYAN, // LEFT SIDE, going upwards
        CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN, // TOP ROW, LEFT TO RIGHT
        CYAN,    CYAN,    CYAN, // RIGHT SIDE, going down
    },
    [MACRO_LAYER] = {
        PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE,  PURPLE, // BOTTOM ROW, RIGHT TO LEFT
        CYAN,    CYAN,    CYAN,    CYAN, // LEFT SIDE, going upwards
        CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN,    CYAN, // TOP ROW, LEFT TO RIGHT
        CYAN,    CYAN,    CYAN, // RIGHT SIDE, going down
    },
};
#elif COLORSCHEME_INDEX == COLORSCHEME_ANALOGDREAMS
const uint8_t PROGMEM borderledmap[][NUM_BORDER_KEYS][3] = {
    [KEY_LAYER] = {
        PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK, PANPNK, // BOTTOM ROW, RIGHT TO LEFT
        PANPNK,  PANPNK,  PANPNK,  PANPNK, // LEFT SIDE, going upwards
        PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK, // TOP ROW, LEFT TO RIGHT
        PANPNK,  PANPNK,  PANPNK, // RIGHT SIDE, going down
    },
    [FUNC_LAYER] = {
        DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN,  DGREEN, // BOTTOM ROW, RIGHT TO LEFT
        PANPNK,  PANPNK,  PANPNK,  PANPNK, // LEFT SIDE, going upwards
        PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK, // TOP ROW, LEFT TO RIGHT
        PANPNK,  PANPNK,  PANPNK, // RIGHT SIDE, going down
    },
    [MACRO_LAYER] = {
        BLU,     BLU,     BLU,     BLU,     BLU,     BLU,     BLU,     BLU,     BLU,     BLU,     BLU,     BLU,     BLU,    // BOTTOM ROW, RIGHT TO LEFT
        PANPNK,  PANPNK,  PANPNK,  PANPNK, // LEFT SIDE, going upwards
        PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK,  PANPNK, // TOP ROW, LEFT TO RIGHT
        PANPNK,  PANPNK,  PANPNK, // RIGHT SIDE, going down
    },
};
#endif


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
        rgb_matrix_set_color(i, r, g, b);
    }

    for (int i = 0; i < NUM_BORDER_KEYS; ++i)
    {
        uint8_t r = 0; uint8_t g = 0; uint8_t b = 0;
        if (caps_on)
        {
            r = 255;
            g = 0;
            b = 0;
        }
        else
        {
            r = pgm_read_byte(&borderledmap[layer][i][0]);
            g = pgm_read_byte(&borderledmap[layer][i][1]);
            b = pgm_read_byte(&borderledmap[layer][i][2]);
        }
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
        case GITADDU:
            if (record->event.pressed)
            {
                SEND_STRING("git add -u" SS_TAP(X_ENT));
            }
            return true;
        case GCMSG:
            if (record->event.pressed)
            {
                SEND_STRING(GCMSGSTR SS_TAP(X_LEFT));
            }
            return true;
        case GST:
            if (record->event.pressed)
            {
                SEND_STRING(GSTSTR SS_TAP(X_ENT));
            }
            return true;
        case GNBRNCH:
            if (record->event.pressed)
            {
                SEND_STRING(GNBRNCHSTR);
            }
            return true;
        case GDREM:
            if (record->event.pressed)
            {
                SEND_STRING(GDREMSTR);
            }
            return true;
        case GAREM:
            if (record->event.pressed)
            {
                SEND_STRING(GAREMSTR);
            }
            return true;
        default:
            return true; //Process all other keycodes normally
    }
}
