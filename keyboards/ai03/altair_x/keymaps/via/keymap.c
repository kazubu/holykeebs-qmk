/* Copyright 2024 ai03 Design Studio */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H
#include "users/holykeebs/holykeebs.h"

enum layers {
  _BASE = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _END,
  _MOUSE,
  _POINTER
};


#define AUTO_MOUSE_LAYER _MOUSE
#define _DRSCL HK_DRAGSCROLL_MODE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    XXXXXXX, XXXXXXX, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX, XXXXXXX, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ESC,
                                   KC_LALT, KC_LGUI, MO(1),   KC_SPC,  KC_ENT,  MO(2),   KC_RALT,  KC_RGUI
    ),

    [1] = LAYOUT(
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        _______, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, MS_BTN1, _______, _______, KC_LEFT, KC_DOWN, KC_UP,  KC_RIGHT, _______, _______,
        _______, XXXXXXX, XXXXXXX, XXXXXXX,  _DRSCL, MS_BTN2, _______, _______, XXXXXXX, XXXXXXX, _______, _______, _______, _______,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [2] = LAYOUT(
        KC_TAB,  KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC, _______, _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,  KC_DEL,
        KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
        KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [3] = LAYOUT(
        QK_BOOT, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, _______,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, XXXXXXX, KC_BRIU, KC_VOLU, XXXXXXX, XXXXXXX, _______, _______,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_F12,
        _______, XXXXXXX, KC_BRID, KC_VOLD, KC_MUTE, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_SCRL, KC_PSCR,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [4] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______, _______, _______, _______, _______, _______, _______
    ),

    [5] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                                   _______, MS_BTN1,  _DRSCL, MS_BTN2, _______, _______, _______, _______
    )

};


#define AML_THRESHOLD 1
#define AML_TIMEOUT_MS 500
static uint16_t auto_pointer_layer_timer = 0;

report_mouse_t pointing_device_task_keymap(report_mouse_t mouse_report) {
  if (abs(mouse_report.x) > AML_THRESHOLD|| abs(mouse_report.y) > AML_THRESHOLD) {
    if (auto_pointer_layer_timer == 0) {
      layer_on(AUTO_MOUSE_LAYER);
    }
    auto_pointer_layer_timer = timer_read();
  }

  return mouse_report;
}

void matrix_scan_user(void) {
  if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= AML_TIMEOUT_MS) {
    auto_pointer_layer_timer = 0;
    layer_off(_MOUSE);
  };
}

layer_state_t layer_state_set_user(layer_state_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

  return state;
}
