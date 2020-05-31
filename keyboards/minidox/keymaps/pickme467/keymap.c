#include QMK_KEYBOARD_H

#define _BASE 0
#define _LOWER 1
#define _RAISE 2
#define _RALT 3

enum {
      LOWER_UPPER_MOD = 0,
      UPPER_LOWER_MOD,
};

void layer_reset(void) {
  layer_off(_LOWER);
  layer_off(_RAISE);
}

void lower_upper_finish(qk_tap_dance_state_t* state, void* user_data) {
  if (state->pressed) {
    switch (state->count) {
    case 1:
      layer_on(_LOWER);
      break;
    default:
      layer_on(_RAISE);
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
    default:
      layer_on(_LOWER);
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
#define FN_RALT MO(_RALT)

#define FN_MUTE KC__MUTE
#define FN_VOLD KC__VOLDOWN
#define FN_VOLU KC__VOLUP
#define FNRA_A RALT(KC_A)
#define FNRA_C RALT(KC_C)
#define FNRA_E RALT(KC_E)
#define FNRA_L RALT(KC_L)
#define FNRA_N RALT(KC_N)
#define FNRA_O RALT(KC_O)
#define FNRA_S RALT(KC_S)
#define FNRA_X RALT(KC_X)
#define FNRA_Z RALT(KC_Z)
#define HYPER KC_F9
#define SUPER KC_F8

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( \
      KC_QUOT,   KC_COMM,    KC_DOT,      KC_P,      KC_Y,            KC_F,      KC_G,      KC_C,      KC_R,      KC_L,\
         KC_A,      KC_O,      KC_E,      KC_U,      KC_I,            KC_D,      KC_H,      KC_T,      KC_N,      KC_S,\
      KC_SCLN,      KC_Q,      KC_J,      KC_K,      KC_X,            KC_B,      KC_M,      KC_W,      KC_V,      KC_Z,\
                            FN_RALT,   KC_LCTL,    FN_DK2,         KC_LALT,    KC_SPC,   KC_RSFT\
  ),

  [_RAISE] = LAYOUT( \
         KC_1,      KC_2,      KC_3,      KC_4,      KC_5,            KC_6,      KC_7,      KC_8,      KC_9,      KC_0,\
       KC_TAB,   KC_COMM,    KC_DOT,   KC_UNDS,   KC_MINS,         KC_PIPE,   KC_SLSH,   KC_PLUS,   KC_QUES,   KC_BSPC,\
       KC_ESC,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,         KC_RCTL,   KC_BSLS,    KC_EQL,   XXXXXXX,    KC_ENT,\
                            KC_LGUI,   KC_LCTL,   XXXXXXX,         KC_LALT,   KC_RGUI,   KC_RSFT\
  ),

  [_LOWER] = LAYOUT( \
        KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,           KC_F6,     KC_F7,     KC_F8,     KC_F9,    KC_F10,\
    KC_INSERT, KC_DELETE,   FN_VOLU,   FN_MUTE,    KC_F11,          KC_F12,   KC_SLCK,   KC_PGUP,   KC_VOLU,   KC_MUTE,\
        RESET,   KC_CLCK,   FN_VOLD,   XXXXXXX,   XXXXXXX,         KC_HOME,    KC_END, KC_PGDOWN,   KC_VOLD,    KC_ENT,\
                            KC_LGUI,   KC_LCTL,   XXXXXXX,         KC_LALT,   KC_RGUI,   KC_RSFT\
 ),

  [_RALT] = LAYOUT( \
      XXXXXXX,    KC_GRV,   KC_TILD,   KC_LBRC,     KC_LT,           KC_GT,   KC_RBRC,    FNRA_C,   XXXXXXX,    FNRA_L,\
       FNRA_A,    FNRA_O,    FNRA_E,   KC_LPRN,   KC_LCBR,         KC_RCBR,   KC_RPRN,     KC_UP,    FNRA_N,    FNRA_S,\
      XXXXXXX,     SUPER,   XXXXXXX,     HYPER,    FNRA_X,         XXXXXXX,   KC_LEFT,   KC_DOWN,  KC_RIGHT,    FNRA_Z,\
                            XXXXXXX,   KC_LCTL,   KC_LGUI,         KC_LALT,    KC_SPC,   KC_RSFT\
  )
};
