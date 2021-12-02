/* Copyright 2021 sekigon-gonnoc
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "pico_eeprom.h"
#include "rgblight.h"
#include "print.h"
#include "analog.h"
#include "pointing_device.h"

uint8_t pointerThreshold = 10;
uint16_t lastTimestamp = 0;
uint8_t x, y, isMoving = 0;
#define X_PIN 27
#define Y_PIN 26
#define LOW_AXIS_VALUE 1
#define REST_AXIS_VALUE 2048
#define HIGH_AXIS_VALUE 4095
#define MAX_COORDINATE_VALUE 127
#define COORDINATE_THRESHOLD_VALUE 64

#define LCTR_Z   MT(MOD_LCTL, KC_Z)
#define LSFT_Esc MT(MOD_LSFT, KC_ESC)
#define LALT_ENT MT(MOD_LALT, KC_ENT)
#define LGUI_BSP MT(MOD_LGUI, KC_BSPC)
#define RALT_ENT MT(MOD_RALT, KC_ENT)
#define RGUI_BSP MT(MOD_RGUI, KC_BSPC)
#define RCTL_SLS MT(MOD_RCTL, KC_SLSH)
#define RSFT_SPC MT(MOD_RSFT, KC_SPC)

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    BASE,
    Fn1,
    Fn2,
    NUM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
    //  KC_TRANSPARENT
        KC_1,   KC_2, KC_3, KC_4, KC_5, LSFT_Esc, MO(Fn1),   KC_6, KC_7, KC_8,    KC_9,   KC_0,     MO(Fn2),   KC_LEFT,
        KC_Q,   KC_W, KC_E, KC_R, KC_T, TT(NUM),  LALT_ENT,  KC_Y, KC_U, KC_I,    KC_O,   KC_P,     RALT_ENT,  KC_UP,
        KC_A,   KC_S, KC_D, KC_F, KC_G, KC_TAB,   LGUI_BSP,  KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,  RGUI_BSP,  KC_DOWN,
        LCTR_Z, KC_X, KC_C, KC_V, KC_B, _______,  _______,   KC_N, KC_M, KC_COMM, KC_DOT, RCTL_SLS, RSFT_SPC,  KC_RGHT
    ),
    [Fn1] = LAYOUT(
        KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_SPC,  _______,  KC_F6,      KC_F7,       KC_F8,       KC_F9,      KC_EJCT,  _______, KC_HOME,
        KC_DEL,   KC_UP,   KC_BSPC, _______, _______, _______, KC_ENT,   KC_GRV,     S(KC_MINUS), S(KC_EQUAL), KC_MINUS,   KC_EQUAL, KC_ENT,  KC_PGUP,
        KC_LEFT,  KC_DOWN, KC_RGHT, _______, _______, _______, KC_BSPC,  S(KC_LCBR), S(KC_RCBR),  KC_LBRC,     KC_RBRC,    KC_QUOT,  KC_BSPC, KC_PGDN,
        _______,  _______, _______, _______, _______, _______, _______,  KC_NUBS,    KC_GRV,      _______,     S(KC_BSLS), KC_BSLS,  KC_SPC,  KC_END
    ),
    [Fn2] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______,  KC_F6,   KC_F7,    KC_F8,   KC_F9,    KC_F10,  _______, _______,
        KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  _______, KC_ENT,   KC_F16,  _______,  KC_MRWD, KC_MFFD,  KC_MPLY, KC_ENT,  _______,
        RGB_M_K, RGB_M_B, RGB_VAI, RGB_HUI, RGB_SAI, _______, KC_BSPC,  RGB_TOG, RGB_MOD,  KC_VOLD, KC_VOLU,  KC_MUTE, KC_BSPC, _______,
        RGB_M_R, RGB_M_G, RGB_VAD, RGB_HUD, RGB_SAD, _______, _______,  RGB_M_P, RGB_M_SW, RGB_M_T, RGB_M_SN, _______, KC_CAPS, _______
    ),
    [NUM] = LAYOUT(
       KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, KC_BTN5, _______, _______,  _______, KC_P7, KC_P8,   KC_P9,   KC_PSLS, _______, _______,
       _______, KC_MS_U, _______, KC_WH_U, _______, _______, _______,  _______, KC_P4, KC_P5,   KC_P6,   KC_PAST, _______, _______,
       KC_MS_L, _______, KC_MS_R, KC_WH_D, _______, _______, _______,  _______, KC_P1, KC_P2,   KC_P3,   KC_PMNS, _______, _______,
       _______, KC_MS_D, KC_WH_L, KC_WH_R, RESET,   _______, _______,  _______, KC_P0, KC_PCMM, KC_PDOT, KC_PPLS, KC_PENT, _______
    )
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=false;
  debug_matrix=false;
  debug_keyboard=false;
  debug_mouse=false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
  return true;
}

int8_t axisCoordinate(uint8_t pin) {
  int8_t direction;
  int16_t range;
  int16_t distance;
  int16_t position = analogReadPin(pin);
  if (position == REST_AXIS_VALUE) {
    return 0;
  } else if (position < REST_AXIS_VALUE) {
    distance = REST_AXIS_VALUE - position;
    range = REST_AXIS_VALUE - LOW_AXIS_VALUE;
    direction = -1;
  } else {
    distance = position - REST_AXIS_VALUE;
    range = HIGH_AXIS_VALUE - REST_AXIS_VALUE;
    direction = 1;
  }
  float percent = (float)distance / range;
  int16_t coordinate = (int16_t)(percent * MAX_COORDINATE_VALUE);
  if (coordinate < 0) {
    return 0;
  } else if (coordinate > MAX_COORDINATE_VALUE) {
    return MAX_COORDINATE_VALUE * direction;
  } else {
    return coordinate * direction;
  }
}

int8_t axisToMouseComponent(uint8_t pin) {
  int coordinate = axisCoordinate(pin);
  if (coordinate == 0) {
    return 0;
  } else {
    return abs(coordinate) * (float)coordinate / 2000;
  }
}

void pointing_device_task(void) {
    report_mouse_t report = pointing_device_get_report();
    if (timer_elapsed(lastTimestamp) > pointerThreshold) {
        lastTimestamp = timer_read();
        if (isMoving == 2) {
            report.buttons = 0x00;
            report.x = -x;
            report.y = -y;
            pointing_device_set_report(report);
            pointing_device_send();
            isMoving = 1;
        } else {
            x = axisToMouseComponent(X_PIN);
            y = axisToMouseComponent(Y_PIN);
            if ((x != 0) | (y != 0)) {
                if (isMoving == 0) {
                    register_code(KC_F4);
                    isMoving = 1;
                } else {
                    report.buttons = 0x01;
                    report.x = x;
                    report.y = y;
                    pointing_device_set_report(report);
                    pointing_device_send();
                    isMoving = 1;
                }
            } else {
                if (isMoving != 0) {
                    unregister_code(KC_F4);
                    isMoving = 0;
                    report.x = 0;
                    report.y = 0;
                    report.buttons = 0x00;
                    //TODO remove incydentaly double click
                    pointing_device_set_report(report);
                    pointing_device_send();
                }
            }
        }
    }
}
