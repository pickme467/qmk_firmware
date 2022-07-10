#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 6

/* key matrix pins */
#define MATRIX_COL_PINS { GP12, GP11, GP10, GP9, GP26, GP14 }
#define MATRIX_ROW_PINS { GP1, GP2, GP3, GP4, GP6 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* number of backlight levels */
#define RGB_DI_PIN GP5

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 8
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 100
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_SNAKE
#define RGBLIGHT_DEFAULT_HUE 100
#define RGBLIGHT_DEFAULT_SAT 255
#define RGBLIGHT_DEFAULT_SPD 20
#endif

#define MOUSEKEY_MOVE_DELTA 2
#define MOUSEKEY_TIME_TO_MAX 240
#define MOUSEKEY_WHEEL_TIME_TO_MAX 240
#define MOUSEKEY_DELAY 40

/* Solenoid */
#define SOLENOID_PIN GP28
