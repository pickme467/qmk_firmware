// Copyright 2022 pickme467 (@pickme467)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x16C0
#define PRODUCT_ID 0x27DB
#define DEVICE_VER 0x0001
#define MANUFACTURER IBM/pickme467
#define PRODUCT IBM Model M (rp2040)
#define SERIAL_NUMBER ""

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 16

#define MATRIX_COL_PINS { GP21, GP18, GP16, GP15, GP14, GP13, GP17, GP22, GP12, GP11, GP10, GP9, GP8, GP28, GP19, GP20}
#define MATRIX_ROW_PINS { GP7,  GP6,  GP5,  GP4,  GP3,  GP2,  GP1,  GP0}

#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
#define MATRIX_HAS_GHOST

/* number of backlight levels */
#define RGB_DI_PIN GP26

#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 8
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 100
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RGB_TEST
#define RGBLIGHT_DEFAULT_HUE 100
#define RGBLIGHT_DEFAULT_SAT 255
#define RGBLIGHT_DEFAULT_SPD 20
#endif

#define MOUSEKEY_MOVE_DELTA 2
#define MOUSEKEY_TIME_TO_MAX 240
#define MOUSEKEY_WHEEL_TIME_TO_MAX 240
#define MOUSEKEY_DELAY 40
