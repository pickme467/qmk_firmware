#include QMK_KEYBOARD_H

#define _DVORAK 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _BRACES 4

enum {
      LOWER_UPPER_MOD = 0,
      UPPER_LOWER_MOD,
};

void layer_reset(void) {
  layer_off(_LOWER);
  layer_off(_RAISE);
  layer_off(_ADJUST);
  layer_off(_BRACES);
}

void lower_upper_finish(qk_tap_dance_state_t* state, void* user_data) {
  if (state->pressed) {
    switch (state->count) {
    case 1:
      layer_on(_LOWER);
      break;
    case 2:
      layer_on(_RAISE);
      break;
    default:
      layer_on(_ADJUST);
       break;
    }
  } else {
    layer_reset();
  }
}

void lower_upper_reset(qk_tap_dance_state_t* state, void* user_data) {
  layer_reset();
}

void upper_lower_finish(qk_tap_dance_state_t* state, void* user_data) {
  if (state->pressed) {
    switch (state->count) {
    case 1:
      layer_on(_RAISE);
      break;
    case 2:
      layer_on(_LOWER);
      break;
    default:
      layer_on(_ADJUST);
       break;
    }
  } else {
    layer_reset();
  }
}

void upper_lower_reset(qk_tap_dance_state_t* state, void* user_data) {
  layer_reset();
}

qk_tap_dance_action_t tap_dance_actions[] =
  {
   [LOWER_UPPER_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, lower_upper_finish, lower_upper_reset, 275),
   [UPPER_LOWER_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, upper_lower_finish, upper_lower_reset, 275)
  };

#define FN_DK1 TD(UPPER_LOWER_MOD)
#define FN_DK2 TD(UPPER_LOWER_MOD)
#define FN_LK1 KC_INSERT
#define FN_LK2 KC_RIGHT
#define FN_LK3 KC_PGDOWN
#define FN_LK4 KC_DELETE
#define FN_RK2 MO(_BRACES)
#define FN_AK1 KC__MUTE
#define FN_AK2 KC__VOLDOWN
#define FN_AK3 KC__VOLUP

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT( \
  //,--------------------------------------------.                    ,--------------------------------------------.
      KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,    KC_L,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                         KC_D,    KC_H,    KC_T,    KC_N,    KC_S,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,\
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 KC_RALT, KC_LCTL,  FN_DK1,     FN_DK2,  KC_SPC, KC_RSFT\
                             //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT( \
  //,--------------------------------------------.                    ,--------------------------------------------.
      KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, XXXXXXX, KC_CLCK,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_HOME,  FN_LK3, KC_PGUP,  KC_END, KC_COMM,                       KC_DOT, KC_LEFT,   KC_UP, KC_DOWN,  FN_LK2,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, KC_LGUI, XXXXXXX,                       FN_LK1,  FN_LK4, KC_RSFT, KC_RCTL,  KC_ENT,\
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 KC_LALT, KC_LCTL, XXXXXXX,    XXXXXXX, KC_LALT,  KC_LGUI\
                             //`--------------------------'  `--------------------------'
    ),

  [_RAISE] = LAYOUT( \
  //,--------------------------------------------.                    ,--------------------------------------------.
         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       KC_TAB, XXXXXXX,  KC_EQL, KC_UNDS, KC_MINS,                      KC_SLSH, KC_BSLS, KC_PLUS, KC_QUES, KC_BSPC,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       KC_ESC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PIPE,  FN_RK2, KC_TILD,  KC_GRV,  KC_ENT,\
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 KC_LALT, KC_LGUI, XXXXXXX,    XXXXXXX, KC_RSFT, KC_LGUI\
                             //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,--------------------------------------------.                    ,--------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT,  KC_F11,                       KC_F12, KC_LALT, KC_RGUI, KC_RCTL, KC_RSFT,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
        RESET, KC_SLCK, XXXXXXX, XXXXXXX,  FN_AK1,                       FN_AK2,  FN_AK3, KC_MUTE, KC_VOLD, KC_VOLU,\
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 KC_LALT, KC_LGUI, _______,    _______, KC_LALT, KC_LGUI\
                             //`--------------------------'  `--------------------------'
 ),

  [_BRACES] = LAYOUT( \
  //,--------------------------------------------.                    ,--------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, XXXXXXX,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX,   KC_LT,   KC_GT,                      XXXXXXX, XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 KC_LALT, KC_LGUI, _______,    _______, KC_LALT, KC_LGUI\
                             //`--------------------------'  `--------------------------'
  )
};
