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

#define MATRIX_COL_PINS { GP8,  GP9, GP10, GP11, GP12, GP13, GP14, GP15, GP16, GP17, GP18, GP19, GP20, GP21, GP22, GP28}
#define MATRIX_ROW_PINS { GP0,  GP1,  GP2,  GP3,  GP4,  GP5,  GP6,  GP7}

#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
#define MATRIX_HAS_GHOST
