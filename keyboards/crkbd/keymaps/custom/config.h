#pragma once

#define VIAL_KEYBOARD_UID {0x3B, 0x6B, 0xA0, 0x29, 0x80, 0x56, 0xED, 0xD1}
#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 1}

#define DYNAMIC_KEYMAP_LAYER_COUNT 3
#define TAPPING_TERM 180

//#define USE_MATRIX_I2C
// #ifdef KEYBOARD_crkbd_rev1_legacy
// #    undef USE_I2C
// #    define USE_SERIAL
// #endif

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

// #define USE_SERIAL_PD2
// #ifdef RGBLIGHT_ENABLE
// #    undef RGBLIGHT_LED_COUNT
// #    define RGBLIGHT_ANIMATIONS
// #    define RGBLIGHT_LED_COUNT 54
// #    undef RGBLED_SPLIT
// #    define RGBLED_SPLIT { 27, 27 }
// #    define RGBLIGHT_LIMIT_VAL 120
// #    define RGBLIGHT_HUE_STEP  10
// #    define RGBLIGHT_SAT_STEP  17
// #    define RGBLIGHT_VAL_STEP  17
// #endif

// #ifdef RGB_MATRIX_ENABLE
// #    define RGB_MATRIX_KEYPRESSES // reacts to keypresses
// // #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
// #    define RGB_MATRIX_SLEEP // turn off effects when suspended
// #    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// // #   define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// // #   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
// #    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
// #    define RGB_MATRIX_HUE_STEP 8
// #    define RGB_MATRIX_SAT_STEP 8
// #    define RGB_MATRIX_VAL_STEP 8
// #    define RGB_MATRIX_SPD_STEP 10
// // #    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
// #endif

// #define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

#define SPLIT_WPM_ENABLE
