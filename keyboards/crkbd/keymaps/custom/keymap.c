#include QMK_KEYBOARD_H

#ifdef VIAL_ENABLE
#    include "vial.h"
#    include "dynamic_keymap.h"
#endif

enum layers {
    _QWERTY,
    _PROGRAM,
    _NUMBERS,
};

#define LAYER_TIMEOUT_MS 30000UL
static uint32_t layer_timeout_timer = 0;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
  LT(_NUMBERS, KC_ESC), KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,   KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  OSM(MOD_LSFT),    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,   TD(5),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL, KC_LGUI, KC_SPC,     KC_ENT,   TO(1), KC_BSPC
                                      //`--------------------------'  `--------------------------'
  ),

  [_PROGRAM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, KC_LALT, LSFT(KC_5), LSFT(KC_6), LSFT(KC_BSLS), KC_MINS,           KC_GRV, LSFT(KC_1), LSFT(KC_7), LSFT(KC_4), KC_SCRL, KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,  KC_DOT, LSFT(KC_3), LSFT(KC_7), KC_BSLS,  KC_PSLS,               KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,   KC_NO,   TD(2),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  OSM(MOD_LSFT), LSFT(KC_4), LSFT(KC_8), LSFT(KC_2), LCTL(KC_GRV), KC_EQL,         KC_LBRC, LSFT(KC_9), LSFT(KC_0), KC_RBRC, KC_NO, TD(3),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            TD(4),   TO(0),  KC_SPC,     KC_ENT,   TO(2), KC_BSPC
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUMBERS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, KC_RGUI,   KC_NO, KC_MPRV, KC_MPLY, KC_MNXT,                    LSFT(KC_4),   KC_7,    KC_8,    KC_9, KC_MINS, KC_PSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI,   KC_NO, KC_VOLU,                       KC_DOT,    KC_4,    KC_5,    KC_6,  KC_EQL, LSFT(KC_8),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD,   KC_NO, KC_VOLD,                         KC_0,    KC_1,    KC_2,    KC_3, KC_SLSH, KC_COMM,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   TO(0),  KC_SPC,     KC_ENT,   TO(1), KC_BSPC
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef VIAL_ENABLE
void eeconfig_init_user(void) {
    vial_init();

#    ifdef VIAL_TAP_DANCE_ENABLE
    static const vial_tap_dance_entry_t default_tap_dances[] = {
        { .on_tap = OSM(MOD_LSFT), .on_hold = KC_LSFT, .on_double_tap = KC_NO,         .on_tap_hold = KC_LSFT, .custom_tapping_term = 100 },
        { .on_tap = OSM(MOD_LCTL), .on_hold = KC_LCTL, .on_double_tap = KC_NO,         .on_tap_hold = KC_NO,   .custom_tapping_term = 180 },
        { .on_tap = KC_PGUP,       .on_hold = KC_HOME, .on_double_tap = KC_NO,         .on_tap_hold = KC_NO,   .custom_tapping_term = 100 },
        { .on_tap = KC_PGDN,       .on_hold = KC_END,  .on_double_tap = KC_NO,         .on_tap_hold = KC_NO,   .custom_tapping_term = 100 },
        { .on_tap = KC_LGUI,       .on_hold = KC_LCTL, .on_double_tap = OSM(MOD_LGUI), .on_tap_hold = KC_NO,   .custom_tapping_term = 180 },
        { .on_tap = OSM(MOD_RALT), .on_hold = KC_RALT, .on_double_tap = KC_CAPS,       .on_tap_hold = KC_NO,   .custom_tapping_term = 180 },
        { .on_tap = KC_NO,         .on_hold = KC_LGUI, .on_double_tap = KC_NO,         .on_tap_hold = KC_NO,   .custom_tapping_term = 100 },
    };
    for (uint8_t i = 0; i < ARRAY_SIZE(default_tap_dances); i++) {
        vial_tap_dance_entry_t td = default_tap_dances[i];
        dynamic_keymap_set_tap_dance(i, &td);
    }
#    endif

#    ifdef VIAL_KEY_OVERRIDE_ENABLE
    static const vial_key_override_entry_t default_key_overrides[] = {
        { .trigger = KC_1,    .replacement = KC_F1,   .layers = 0xFFFF, .trigger_mods = MOD_BIT(KC_RGUI), .negative_mod_mask = 0, .suppressed_mods = 0, .options = 135 },
        { .trigger = KC_2,    .replacement = KC_F2,   .layers = 0xFFFF, .trigger_mods = MOD_BIT(KC_RGUI), .negative_mod_mask = 0, .suppressed_mods = 0, .options = 135 },
        { .trigger = KC_3,    .replacement = KC_F3,   .layers = 0xFFFF, .trigger_mods = MOD_BIT(KC_RGUI), .negative_mod_mask = 0, .suppressed_mods = 0, .options = 135 },
        { .trigger = KC_4,    .replacement = KC_F4,   .layers = 0xFFFF, .trigger_mods = MOD_BIT(KC_RGUI), .negative_mod_mask = 0, .suppressed_mods = 0, .options = 135 },
        { .trigger = KC_5,    .replacement = KC_F5,   .layers = 0xFFFF, .trigger_mods = MOD_BIT(KC_RGUI), .negative_mod_mask = 0, .suppressed_mods = 0, .options = 7 },
        { .trigger = KC_6,    .replacement = KC_F6,   .layers = 0xFFFF, .trigger_mods = MOD_BIT(KC_RGUI), .negative_mod_mask = 0, .suppressed_mods = 0, .options = 135 },
        { .trigger = KC_7,    .replacement = KC_F7,   .layers = 0xFFFF, .trigger_mods = MOD_BIT(KC_RGUI), .negative_mod_mask = 0, .suppressed_mods = 0, .options = 135 },
        { .trigger = KC_8,    .replacement = KC_F8,   .layers = 0xFFFF, .trigger_mods = MOD_BIT(KC_RGUI), .negative_mod_mask = 0, .suppressed_mods = 0, .options = 135 },
        { .trigger = KC_9,    .replacement = KC_F9,   .layers = 0xFFFF, .trigger_mods = MOD_BIT(KC_RGUI), .negative_mod_mask = 0, .suppressed_mods = 0, .options = 135 },
        { .trigger = KC_MINS, .replacement = KC_F10,  .layers = 0xFFFF, .trigger_mods = MOD_BIT(KC_RGUI), .negative_mod_mask = 0, .suppressed_mods = 0, .options = 135 },
        { .trigger = KC_EQL,  .replacement = KC_F11,  .layers = 0xFFFF, .trigger_mods = MOD_BIT(KC_RGUI), .negative_mod_mask = 0, .suppressed_mods = 0, .options = 135 },
        { .trigger = KC_SLSH, .replacement = KC_F12,  .layers = 0xFFFF, .trigger_mods = MOD_BIT(KC_RGUI), .negative_mod_mask = 0, .suppressed_mods = 0, .options = 135 },
        { .trigger = KC_PSLS, .replacement = KC_PSCR, .layers = 0xFFFF, .trigger_mods = MOD_BIT(KC_RGUI), .negative_mod_mask = 0, .suppressed_mods = 0, .options = 7 },
    };
    for (uint8_t i = 0; i < ARRAY_SIZE(default_key_overrides); i++) {
        vial_key_override_entry_t ko = default_key_overrides[i];
        dynamic_keymap_set_key_override(i, &ko);
    }
#    endif
}
#endif

#ifdef OLED_ENABLE
#include <stdio.h>

/* 32 * 24 Tux penguin logo (3 pages x 32 cols, LSB = top pixel) */
static const char PROGMEM tux_logo[3][32] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xfc, 0x9e, 0x6e, 0x6f, 0x9f, 0xff, 0xff, 0xff, 0xff, 0x9f, 0x6f, 0x6e, 0x9e, 0xfc, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x80, 0xe0, 0xf0, 0xf8, 0x3c, 0x1f, 0x0f, 0x07, 0x07, 0x07, 0x06, 0x04, 0x04, 0x04, 0x04, 0x06, 0x07, 0x07, 0x07, 0x0f, 0x1f, 0x3c, 0xf8, 0xf0, 0xe0, 0x80, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x43, 0x6f, 0x7f, 0x7c, 0x78, 0x70, 0x70, 0x60, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x60, 0x70, 0x70, 0x78, 0x7c, 0x7f, 0x6f, 0x43, 0x00, 0x00, 0x00},
};

/* 7 * 8 modifier glyphs: Shift, Ctrl, Alt, Super */
static const uint8_t PROGMEM mod_glyphs[4][7] = {
    {0x00, 0x08, 0x0c, 0x7e, 0x0c, 0x08, 0x00}, // Shift
    {0x00, 0x08, 0x04, 0x02, 0x04, 0x08, 0x00}, // Ctrl
    {0x00, 0x38, 0x14, 0x12, 0x14, 0x38, 0x00}, // Alt
    {0x00, 0x18, 0x24, 0x42, 0x24, 0x18, 0x00}, // Super
};

/* KEYBOARD PET START */

/* settings */
#    define MIN_WALK_SPEED      10
#    define MIN_RUN_SPEED       40

/* advanced settings */
#    define ANIM_FRAME_DURATION 200  // how long each frame lasts in ms
#    define ANIM_SIZE           96   // number of bytes in array. If you change sprites, minimize for adequate firmware size. max is 1024

/* timers */
uint32_t anim_timer = 0;

/* current frame */
uint8_t current_frame = 0;

/* status variables */
int   current_wpm = 0;
led_t led_usb_state;

bool isSneaking = false;
bool isJumping  = false;
bool showedJump = true;

/* logic */
static void render_luna(int LUNA_X, int LUNA_Y) {
    /* Sit */
    static const char PROGMEM sit[2][ANIM_SIZE] = {/* 'sit1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x68, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x06, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'sit2', 32x22px */
                                                   {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x1c, 0x02, 0x05, 0x02, 0x24, 0x04, 0x04, 0x02, 0xa9, 0x1e, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x90, 0x08, 0x18, 0x60, 0x10, 0x08, 0x04, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x0e, 0x82, 0x7c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x0c, 0x10, 0x10, 0x20, 0x20, 0x20, 0x28, 0x3e, 0x1c, 0x20, 0x20, 0x3e, 0x0f, 0x11, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};

    /* Walk */
    static const char PROGMEM walk[2][ANIM_SIZE] = {/* 'walk1', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x10, 0x90, 0x90, 0x90, 0xa0, 0xc0, 0x80, 0x80, 0x80, 0x70, 0x08, 0x14, 0x08, 0x90, 0x10, 0x10, 0x08, 0xa4, 0x78, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x08, 0xfc, 0x01, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0xea, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x03, 0x06, 0x18, 0x20, 0x20, 0x3c, 0x0c, 0x12, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'walk2', 32x22px */
                                                    {
                                                        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20, 0x20, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x28, 0x10, 0x20, 0x20, 0x20, 0x10, 0x48, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x20, 0xf8, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x30, 0xd5, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x02, 0x1c, 0x14, 0x08, 0x10, 0x20, 0x2c, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Run */
    static const char PROGMEM run[2][ANIM_SIZE] = {/* 'run1', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0x00, 0xe0, 0x10, 0x08, 0x08, 0xc8, 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0xc4, 0xa4, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x58, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x09, 0x04, 0x04, 0x04, 0x04, 0x02, 0x03, 0x02, 0x01, 0x01, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   },

                                                   /* 'run2', 32x22px */
                                                   {
                                                       0x00, 0x00, 0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x78, 0x28, 0x08, 0x10, 0x20, 0x30, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x10, 0xb0, 0x50, 0x55, 0x20, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x1e, 0x20, 0x20, 0x18, 0x0c, 0x14, 0x1e, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                   }};

    /* Bark */
    static const char PROGMEM bark[2][ANIM_SIZE] = {/* 'bark1', 32x22px */
                                                    {
                                                        0x00, 0xc0, 0x20, 0x10, 0xd0, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x3c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc8, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    },

                                                    /* 'bark2', 32x22px */
                                                    {
                                                        0x00, 0xe0, 0x10, 0x10, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x40, 0x40, 0x2c, 0x14, 0x04, 0x08, 0x90, 0x18, 0x04, 0x08, 0xb0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x04, 0x08, 0x10, 0x11, 0xf9, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0x48, 0x28, 0x2a, 0x10, 0x0f, 0x20, 0x4a, 0x09, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x0c, 0x10, 0x20, 0x28, 0x37, 0x02, 0x02, 0x04, 0x08, 0x10, 0x26, 0x2b, 0x32, 0x04, 0x05, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                    }};

    /* Sneak */
    static const char PROGMEM sneak[2][ANIM_SIZE] = {/* 'sneak1', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x80, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x04, 0x04, 0x04, 0x03, 0x01, 0x00, 0x00, 0x09, 0x01, 0x80, 0x80, 0xab, 0x04, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x1c, 0x20, 0x20, 0x3c, 0x0f, 0x11, 0x1f, 0x02, 0x06, 0x18, 0x20, 0x20, 0x38, 0x08, 0x10, 0x18, 0x04, 0x04, 0x02, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00,
                                                     },

                                                     /* 'sneak2', 32x22px */
                                                     {
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xa0, 0x20, 0x40, 0x80, 0xc0, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x41, 0xf0, 0x04, 0x02, 0x02, 0x02, 0x03, 0x02, 0x02, 0x02, 0x04, 0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x40, 0x40, 0x55, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x20, 0x30, 0x0c, 0x02, 0x05, 0x09, 0x12, 0x1e, 0x04, 0x18, 0x10, 0x08, 0x10, 0x20, 0x28, 0x34, 0x06, 0x02, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                     }};

    /* animation */
    void animate_luna(void) {
        /* jump */
        if (isJumping || !showedJump) {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y + 2);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y - 1);

            showedJump = true;
        } else {
            /* clear */
            oled_set_cursor(LUNA_X, LUNA_Y - 1);
            oled_write("     ", false);

            oled_set_cursor(LUNA_X, LUNA_Y);
        }

        /* switch frame */
        current_frame = (current_frame + 1) % 2;

        /* current status */
        if (led_usb_state.caps_lock) {
            oled_write_raw_P(bark[current_frame], ANIM_SIZE);

        } else if (isSneaking) {
            oled_write_raw_P(sneak[current_frame], ANIM_SIZE);

        } else if (current_wpm <= MIN_WALK_SPEED) {
            oled_write_raw_P(sit[current_frame], ANIM_SIZE);

        } else if (current_wpm <= MIN_RUN_SPEED) {
            oled_write_raw_P(walk[current_frame], ANIM_SIZE);

        } else {
            oled_write_raw_P(run[current_frame], ANIM_SIZE);
        }
    }

    /* animation timer */
    if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animate_luna();
    }
}
/* KEYBOARD PET END */

/* 24x24 layer icons (3 pages x 24 cols, LSB = top pixel) */
static const char PROGMEM icon_base[3][24] = {
    {0xf0, 0xf8, 0x0c, 0x06, 0x66, 0x66, 0x06, 0x66, 0x66, 0x06, 0x66, 0x66, 0x06, 0x66, 0x66, 0x06, 0x66, 0x66, 0x06, 0x66, 0x0c, 0xf8, 0xf0, 0x00},
    {0xff, 0xff, 0x00, 0x00, 0x66, 0x66, 0x00, 0x66, 0x66, 0x00, 0x66, 0x66, 0x00, 0x66, 0x66, 0x00, 0x66, 0x66, 0x00, 0x66, 0x00, 0xff, 0xff, 0x00},
    {0x0f, 0x1f, 0x30, 0x60, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x60, 0x30, 0x1f, 0x0f, 0x00},
};

static const char PROGMEM icon_prog[3][24] = {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xfc, 0x0e, 0x06, 0x06, 0x00, 0x00, 0x00, 0x06, 0x06, 0x0e, 0xfc, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x18, 0x3c, 0x7e, 0xe7, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc3, 0xe7, 0x7e, 0x3c, 0x18, 0x00, 0x00},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x3f, 0x70, 0x60, 0x60, 0x00, 0x00, 0x00, 0x60, 0x60, 0x70, 0x3f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
};

static const char PROGMEM icon_nums[3][24] = {
    {0x00, 0x00, 0x00, 0xc0, 0xc0, 0xc0, 0xf8, 0xfc, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xf8, 0xfc, 0xc0, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0xc6, 0xc7, 0xc7, 0xc6, 0xff, 0xff, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xff, 0xff, 0xc6, 0xc6, 0xc6, 0xc6, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x00, 0x03, 0x03, 0x03, 0x03, 0x1f, 0x3f, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x1f, 0x3f, 0x03, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00},
};

static void print_logo_narrow(void) {
    uint8_t layer = get_highest_layer(layer_state);
    static uint8_t last_layer = 0xFF;

    if (layer != last_layer) {
        last_layer = layer;
        const char (*icon)[24] = icon_base;
        const char *label = "BASE";
        switch (layer) {
            case _QWERTY:
                icon  = icon_base;
                label = "BASE";
                break;
            case _PROGRAM:
                icon  = icon_prog;
                label = "PROG";
                break;
            case _NUMBERS:
                icon  = icon_nums;
                label = "NUMS";
                break;
            default:
                icon  = icon_base;
                label = "????";
                break;
        }
        for (uint8_t page = 0; page < 3; page++) {
            oled_set_cursor(1, page + 1);
            oled_write_raw_P(icon[page], 24);
        }
        oled_set_cursor(1, 5);
        oled_write(label, false);
    }

    /* bottom status bar: corne + wpm */
    uint8_t n = get_current_wpm();
    static uint8_t last_wpm = 0xFF;
    if (n != last_wpm) {
        last_wpm = n;
        char wpm_str[4];
        wpm_str[3] = '\0';
        wpm_str[2] = '0' + n % 10;
        wpm_str[1] = '0' + (n /= 10) % 10;
        wpm_str[0] = '0' + n / 10;

        oled_set_cursor(1, 10);
        oled_write("WPM", false);
        oled_set_cursor(1, 11);
        oled_write(wpm_str, false);
        oled_set_cursor(0, 14);
        oled_write("corne", false);
    }
}

static void print_status_narrow(void) {
    /* Tux penguin at top (rows 0..2) */
    for (uint8_t page = 0; page < 3; page++) {
        oled_set_cursor(0, page);
        oled_write_raw_P(tux_logo[page], 32);
    }

    /* Live modifier symbol strip (row 5): Shift, Ctrl, Alt, Super */
    static const uint8_t mod_masks[4] = {MOD_MASK_SHIFT, MOD_MASK_CTRL, MOD_MASK_ALT, MOD_MASK_GUI};
    uint8_t mods = get_mods() | get_oneshot_mods();
    char mod_row[31] = {0};
    for (uint8_t i = 0; i < 4; i++) {
        uint8_t inv = (mods & mod_masks[i]) ? 0xFF : 0x00;
        for (uint8_t x = 0; x < 7; x++) {
            mod_row[i * 8 + x] = (char)(pgm_read_byte(&mod_glyphs[i][x]) ^ inv);
        }
    }
    oled_set_cursor(0, 5);
    oled_write_raw(mod_row, sizeof(mod_row));

    /* Caps lock indicator above Luna (row 9) */
    oled_set_cursor(0, 9);
    oled_write(led_usb_state.caps_lock ? "WOOF!" : "     ", led_usb_state.caps_lock);

    /* KEYBOARD PET RENDER START */
    render_luna(0, 11);
    /* KEYBOARD PET RENDER END */
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
#if OLED_TIMEOUT > 0
    if (is_keyboard_master()) {
        if (last_input_activity_elapsed() > OLED_TIMEOUT && last_led_activity_elapsed() > OLED_TIMEOUT) {
            oled_off();
            return false;
        } else {
            oled_on();
        }
    } else if (!is_oled_on()) {
        return false;
    }
#endif
    /* KEYBOARD PET VARIABLES START */
    current_wpm   = get_current_wpm();
    led_usb_state = host_keyboard_led_state();
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        print_logo_narrow();
    }
    return false;
}

typedef struct {
    uint16_t keycode;
    uint16_t on_tap;
    uint16_t on_hold;
    uint16_t on_double;
    uint16_t tapping_term;
} qmk_td_cfg_t;

typedef struct {
    uint8_t  count;
    bool     pressed;
    bool     held;
    uint32_t timer;
} qmk_td_state_t;

static const qmk_td_cfg_t qmk_tds[] = {
    { QK_TAP_DANCE + 2, KC_PGUP,       KC_HOME, KC_NO,         100 },
    { QK_TAP_DANCE + 3, KC_PGDN,       KC_END,  KC_NO,         100 },
    { QK_TAP_DANCE + 4, KC_LGUI,       KC_LCTL, OSM(MOD_LGUI), 180 },
    { QK_TAP_DANCE + 5, OSM(MOD_RALT), KC_RALT, KC_CAPS,       180 },
};
static qmk_td_state_t qmk_td_states[ARRAY_SIZE(qmk_tds)];

static void fire_td_action(uint16_t kc) {
    if (kc >= QK_ONE_SHOT_MOD && kc <= QK_ONE_SHOT_MOD_MAX) {
        add_oneshot_mods(kc & 0x1F);
    } else if (kc != KC_NO) {
        tap_code(kc);
    }
}

static int8_t find_qmk_td(uint16_t keycode) {
    for (uint8_t i = 0; i < ARRAY_SIZE(qmk_tds); i++) {
        if (qmk_tds[i].keycode == keycode) {
            return (int8_t)i;
        }
    }
    return -1;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        layer_timeout_timer = timer_read32();
    }

    int8_t td_idx = find_qmk_td(keycode);
    if (td_idx >= 0) {
        const qmk_td_cfg_t *cfg = &qmk_tds[td_idx];
        qmk_td_state_t     *st  = &qmk_td_states[td_idx];
        if (record->event.pressed) {
            st->pressed = true;
            if (st->count == 0) {
                st->count = 1;
                st->timer = timer_read32();
            } else {
                st->count = 0;
                fire_td_action(cfg->on_double);
            }
        } else {
            st->pressed = false;
            if (st->held) {
                unregister_code(cfg->on_hold);
                st->held  = false;
                st->count = 0;
            } else if (st->count == 1) {
                if (cfg->on_double == KC_NO) {
                    st->count = 0;
                    fire_td_action(cfg->on_tap);
                } else {
                    st->timer = timer_read32();
                }
            }
        }
        return false;
    }

    if (record->event.pressed) {
        for (uint8_t i = 0; i < ARRAY_SIZE(qmk_tds); i++) {
            qmk_td_state_t *st = &qmk_td_states[i];
            if (st->count == 1 && !st->held) {
                if (st->pressed) {
                    register_code(qmk_tds[i].on_hold);
                    st->held = true;
                } else {
                    fire_td_action(qmk_tds[i].on_tap);
                    st->count = 0;
                }
            }
        }
    }

    switch (keycode) {
        /* KEYBOARD PET STATUS START */
        case KC_LCTL:
        case KC_RCTL:
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
            break;
        case KC_SPC:
            if (record->event.pressed) {
                isJumping  = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
            break;
        /* KEYBOARD PET STATUS END */
    }
    return true;
}
#endif // OLED_ENABLE

layer_state_t layer_state_set_user(layer_state_t state) {
    if (get_highest_layer(state) != _QWERTY) {
        layer_timeout_timer = timer_read32();
    }
    return state;
}

void matrix_scan_user(void) {
    for (uint8_t i = 0; i < ARRAY_SIZE(qmk_tds); i++) {
        const qmk_td_cfg_t *cfg = &qmk_tds[i];
        qmk_td_state_t     *st  = &qmk_td_states[i];
        if (st->count == 1 && !st->held) {
            if (st->pressed && timer_elapsed32(st->timer) >= cfg->tapping_term) {
                register_code(cfg->on_hold);
                st->held = true;
            } else if (!st->pressed && cfg->on_double != KC_NO && timer_elapsed32(st->timer) >= 200) {
                fire_td_action(cfg->on_tap);
                st->count = 0;
            }
        }
    }
    if (is_keyboard_master() &&
        get_highest_layer(layer_state) != _QWERTY &&
        timer_elapsed32(layer_timeout_timer) >= LAYER_TIMEOUT_MS) {
        layer_clear();
    }
}
