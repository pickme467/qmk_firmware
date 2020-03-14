#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _DVORAK 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
};

// Defines for task manager and such
#define CALTDEL LCTL(LALT(KC_DEL))
#define TSKMGR LCTL(LSFT(KC_ESC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT( \
  //,--------------------------------------------.                    ,--------------------------------------------.
      KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,    KC_L,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
         KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                         KC_D,    KC_H,    KC_T,    KC_N,    KC_S,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,\
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 KC_RALT,  KC_LCTL,  LOWER,      RAISE,  KC_SPC, KC_RSFT\
                             //`--------------------------'  `--------------------------'

  ),

  [_LOWER] = LAYOUT( \
  //,--------------------------------------------.                    ,--------------------------------------------.
         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_HOME, KC_PGDOWN, KC_PGUP, KC_END, KC_INSERT,                   KC_SLSH, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR,  KC_ENT, KC_BSPC, \
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 KC_LALT, KC_LCTL,   LOWER,      RAISE, KC_LALT,  KC_LGUI\
                             //`--------------------------'  `--------------------------'
    ),

  [_RAISE] = LAYOUT( \
  //,--------------------------------------------.                    ,--------------------------------------------.
         KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       KC_TAB, KC_LCBR, KC_LBRC, KC_LPRN, KC_BSLS,                      KC_SLSH, KC_RPRN, KC_RBRC, KC_RCBR, KC_PIPE,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
       KC_ESC, KC_CLCK,  KC_EQL, KC_UNDS, KC_TILD,                       KC_GRV, KC_MINS, KC_PLUS,  KC_ENT, KC_BSPC,\
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 KC_LALT, KC_LGUI,   LOWER,      RAISE, KC_RCTL, KC_LGUI\
                             //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,--------------------------------------------.                    ,--------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
      KC_LSFT, KC_LCTL, KC_LGUI, KC_LALT,  KC_F11,                       KC_F12, KC_LALT, KC_RGUI, KC_RCTL, KC_RSFT,\
  //|--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------|
        RESET, KC_SLCK, XXXXXXX, KC_DELETE, KC__MUTE,             KC__VOLDOWN, KC__VOLUP, KC_MUTE, KC_VOLD, KC_VOLU,\
  //|--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, XXXXXXX,   LOWER,      RAISE, XXXXXXX, XXXXXXX\
                             //`--------------------------'  `--------------------------'
  )
};

void persistant_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
