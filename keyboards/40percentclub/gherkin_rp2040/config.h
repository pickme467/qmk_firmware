#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 6

/* key matrix pins */
#define MATRIX_COL_PINS { GP12, GP11, GP10, GP9, GP26, GP14 }
#define MATRIX_ROW_PINS { GP1, GP2, GP3, GP4, GP6 }

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

/* Solenoid */
#define SOLENOID_PIN GP28
#define SOLENOID_DEFAULT_DWELL 1
