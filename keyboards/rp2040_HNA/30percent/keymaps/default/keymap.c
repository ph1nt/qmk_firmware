#include QMK_KEYBOARD_H
#include "pico_eeprom.h"
#include "print.h"

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _FNC,
    _ADJUST,
    _NONE,
};

#define LOWER LT(_LOWER, KC_TAB)
#define RAISE LT(_RAISE, KC_BSPACE)
#define FNC MO(_FNC)

#define LCBRACKET LSFT(KC_LBRACKET)
#define RCBRACKET LSFT(KC_RBRACKET)
#define RETURN LSFT(KC_ENTER)
#define ALT_SPACE MT(MOD_RALT, KC_SPACE)
#define SHIFT_ENTER MT(MOD_LSFT, KC_ENTER)
#define ALT_LEFT LALT(KC_LEFT)
#define ALT_DOWN LALT(KC_DOWN)
#define ALT_UP   LALT(KC_UP)
#define ALT_RIGHT LALT(KC_RIGHT)
//-------- home line ----------
#define MC_A MT(MOD_LSFT, KC_A)
#define MC_S MT(MOD_LCTL, KC_S)
#define MC_D MT(MOD_LALT, KC_D)
#define MC_F MT(MOD_LCMD, KC_F)
#define FN_G LT(_FNC, KC_G)
#define FN_H LT(_FNC, KC_H)
#define MC_J MT(MOD_RCMD, KC_J)
#define MC_K MT(MOD_RALT, KC_K)
#define MC_L MT(MOD_RCTL, KC_L)
#define MC_SC MT(MOD_RSFT, KC_SCOLON)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_Q,           KC_W,           KC_E,           KC_R,           KC_T,           KC_Y,           KC_U,           KC_I,           KC_O,           KC_P,
    MC_A,           MC_S,           MC_D,           MC_F,           FN_G,           FN_H,           MC_J,           MC_K,           MC_L,           MC_SC,
    KC_Z,           KC_X,           KC_C,           KC_V,           KC_B,           KC_N,           KC_M,           KC_COMMA,       KC_DOT,         KC_SLASH,
                                                                    ALT_SPACE,      LOWER,          SHIFT_ENTER,    RAISE
  ),
  [_LOWER] = LAYOUT(
    KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,        KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN,
    KC_NONUS_HASH,  KC_TILD,        KC_SLASH,       LCBRACKET,      KC_LBRACKET,    KC_RBRACKET,    RCBRACKET,      KC_BSLASH,      KC_MINUS,       KC_EQUAL,
    KC_CAPSLOCK,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NONUS_HASH,  KC_NONUS_BSLASH,KC_UNDS,        KC_PLUS,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_DELETE
  ),
  [_RAISE] = LAYOUT(
    KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,
    KC_ESC,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [_FNC] = LAYOUT(
    KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_F11,         KC_F12,         KC_F13,         KC_F14,         KC_F15,         KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
  [_NONE] = LAYOUT(
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT
  ),
};

/*
  [_LOWER] = LAYOUT(
    KC_GRAVE,       KC_EXLM,        KC_AT,          KC_HASH,        KC_DLR,         KC_PERC,        KC_CIRC,        KC_AMPR,        KC_ASTR,        KC_LPRN,        KC_RPRN,        KC_TRANSPARENT,
    KC_DELETE,      KC_TILD,        BL_TOGG,        KC_SLASH,       LCBRACKET,      KC_LBRACKET,    KC_RBRACKET,    RCBRACKET,      KC_BSLASH,      KC_MINUS,       KC_EQUAL,       RETURN,
    KC_CAPSLOCK,    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_NONUS_HASH,  KC_NONUS_BSLASH,KC_UNDS,        KC_PLUS,        KC_PIPE,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_HOME,        KC_PGDOWN,      KC_PGUP,        KC_END
  ),
  [_RAISE] = LAYOUT(
    KC_TILD,        KC_1,           KC_2,           KC_3,           KC_4,           KC_5,           KC_6,           KC_7,           KC_8,           KC_9,           KC_0,           KC_KP_SLASH,
    KC_GRAVE,       KC_MS_BTN1,     KC_MS_UP,       KC_MS_BTN2,     KC_MS_WH_UP,    KC_MS_ACCEL0,   KC_MS_ACCEL1,   KC_4,           KC_5,           KC_6,           KC_KP_PLUS,     KC_KP_ASTERISK,
    KC_TRANSPARENT, KC_MS_LEFT,     KC_MS_DOWN,     KC_MS_RIGHT,    KC_MS_WH_DOWN,  KC_MS_WH_LEFT,  KC_MS_WH_RIGHT, KC_1,           KC_2,           KC_3,           KC_KP_MINUS,    KC_KP_ENTER,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_0,           KC_DOT,         KC_COMMA,       KC_KP_EQUAL
  ),
  [_FNC] = LAYOUT(
    KC_MEDIA_EJECT, KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_DELETE,
    KC_F15,         KC_F6,          KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_LEFT,        KC_DOWN,        KC_UP,          KC_RIGHT,       KC_TRANSPARENT, KC_MEDIA_NEXT_TRACK,
    KC_F14,         KC_F11,         KC_F12,         KC_F13,         KC_F14,         KC_F15,         ALT_LEFT,       ALT_DOWN,       ALT_UP,         ALT_RIGHT,      KC_TRANSPARENT, KC_MEDIA_PREV_TRACK,
    KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, KC_TRANSPARENT, RESET,          KC_TRANSPARENT, KC_WAKE,        KC_TRANSPARENT, KC_AUDIO_MUTE,  KC_AUDIO_VOL_DOWN,KC_AUDIO_VOL_UP,KC_MEDIA_PLAY_PAUSE
*/
void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  debug_keyboard=true;
  debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
  return true;
}
