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

/* number of backlight levels */
#define RGB_DI_PIN GP5
#define DRIVER_LED_TOTAL 8
// defined(STM32F0XX) || defined(STM32F1XX) || defined(GD32VF103) || defined(STM32F3XX) || defined(STM32F4XX) || defined(STM32L0XX)

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

/* Solenoid */
#define SOLENOID_PIN GP28
