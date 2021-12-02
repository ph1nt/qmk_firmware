#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x0F1A
#define DEVICE_VER   0x0003
#define MANUFACTURER HNA
#define PRODUCT      30percent

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 9

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
#define MATRIX_COL_PINS { 6, 7, 8, 9, 10, 11, 12, 13, 14 }
//TODO #define ENCODER
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
