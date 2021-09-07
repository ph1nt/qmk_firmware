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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    BASE,
    Fn1,
    Fn2,
    NUM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_1,               KC_2, KC_3, KC_4, KC_5, KC_ESC,      Fn1,                   KC_6, KC_7, KC_8,    KC_9,   KC_0,    Fn2,                   KC_LEFT,
        KC_Q,               KC_W, KC_E, KC_R, KC_T, NUM,         MT(MOD_LALT, KC_ENT),  KC_Y, KC_U, KC_I,    KC_O,   KC_P,    MT(MOD_RALT, KC_ENT),  KC_UP,
        KC_A,               KC_S, KC_D, KC_F, KC_G, KC_TAB,      MT(MOD_LGUI, KC_BSPC), KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, MT(MOD_RGUI, KC_BSPC), KC_DOWN,
        MT(MOD_LCTL, KC_Z), KC_X, KC_C, KC_V, KC_B, _______,     _______,               KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, MT(MOD_RSFT, KC_SPC),  KC_RGHT
    ),
    [Fn1] = LAYOUT(
        KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,      _______,      Fn1,         KC_F6,       KC_F7,         KC_F8,         KC_F9,         KC_EJCT,         Fn2,         KC_HOME,
        KC_DEL,      KC_UP,       KC_BSPC,    _______,     _______,     _______,     _______,      KC_GRV,      S(KC_MINUS),   S(KC_EQUAL),   KC_MINUS,      KC_EQUAL,        _______,      KC_PGUP,
        KC_LEFT,     KC_DOWN,     KC_RGHT,    _______,     _______,     _______,     _______,      S(KC_LCBR),  S(KC_RCBR),    KC_LBRC,       KC_RBRC,       KC_QUOT,         _______,      KC_PGDN,
        _______,     _______,     _______,    _______,     _______,     _______,     _______,      KC_NUBS,     KC_GRV,        _______,       S(KC_BSLS),    KC_BSLS,         _______,      KC_END
    ),
    [Fn2] = LAYOUT(
        KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,      _______,      Fn1,         KC_F6,       KC_F7,         KC_F8,         KC_F9,         KC_F10,         Fn2,         _______,
        KC_F11,      KC_F12,      KC_F13,      KC_F14,      KC_F15,     _______,     _______,      KC_F16,      _______,       KC_MRWD,       KC_MFFD,       KC_MPLY,        _______,     _______,
        RGB_M_K,     RGB_M_B,     RGB_VAI,     RGB_HUI,     RGB_SAI,    _______,     _______,      RGB_TOG,     RGB_MOD,       KC_VOLD,       KC_VOLU,       KC_MUTE,        _______,     _______,
        RGB_M_R,     RGB_M_G,     RGB_VAD,     RGB_HUD,     RGB_SAD,    _______,     _______,      RGB_M_P,     _______,       _______,       _______,       _______,        KC_CAPS,     _______
    ),
    [NUM] = LAYOUT(
       KC_BTN1,     KC_BTN2,     KC_BTN3,     KC_BTN4,     KC_BTN5,     _______,     _______,     _______,      KC_P7,         KC_P8,         KC_P9,         KC_PSLS,        _______,     _______,
       _______,     KC_MS_U,     _______,     KC_WH_U,     _______,     _______,     _______,     _______,      KC_P4,         KC_P5,         KC_P6,         KC_PAST,        _______,     _______,
       KC_MS_L,     _______,     KC_MS_R,     KC_WH_D,     _______,     _______,     _______,     _______,      KC_P1,         KC_P2,         KC_P3,         KC_PMNS,        _______,     _______,
       _______,     KC_MS_D,     KC_WH_L,     KC_WH_R,     _______,     _______,     _______,     _______,      KC_P0,         KC_PCMM,       KC_PDOT,       KC_PPLS,        KC_PENT,     _______
    )
};
