#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x0F1A
#define DEVICE_VER   0x0001
#define MANUFACTURER HNA
#define PRODUCT      rp2040_planck

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12

//#define DEBUG_MATRIX_SCAN_RATE
#define DEBUG_ACTION

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { 2, 3, 4, 5 }
//#define MATRIX_COL_PINS { 15, 14, 13, 12, 11, 10, 21, 20, 19, 18, 16, 17 }
#define MATRIX_COL_PINS { 9, 14, 13, 12, 11, 10, 21, 20, 19, 18, 16, 17 }
//#define MATRIX_COL_PINS { 18, 19, 20, 21, 22, 16, 17, 6, 7, 8, 9, 10, 11, 12 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
//#define DIODE_DIRECTION COL2ROW
#define DIODE_DIRECTION ROW2COL

#define TAPPING_TOGGLE 2
#define BACKLIGHT_PIN 25
#define BACKLIGHT_LIMIT_VAL 120
#define BACKLIGHT_CAPS_LOCK
/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5
/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
