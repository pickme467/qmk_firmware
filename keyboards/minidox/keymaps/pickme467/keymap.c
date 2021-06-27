#include QMK_KEYBOARD_H

enum {
	BASE = 0,
	LOWER,
  RAISE,
	RALT,
};

enum {
	UPPER_LOWER_MOD = 0,
	RALT_GUI_MOD,
	LALT_SHIFT_MOD,
	SHIFT_GUI_MOD,
};

void layer_reset(void) {
  layer_off(LOWER);
  layer_off(RAISE);
}

void upper_lower_finish(qk_tap_dance_state_t* state, void* user_data) {
  if (state->pressed) {
    switch (state->count) {
    case 1:
      layer_on(RAISE);
      break;
    default:
      layer_on(LOWER);
      break;
    }
  } else {
    layer_reset();
  }
}

void upper_lower_reset(qk_tap_dance_state_t* state, void* user_data) {
  layer_reset();
}

void ralt_gui_finish(qk_tap_dance_state_t* state, void* user_data) {
	switch (state->count) {
	case 1:
		layer_on(RALT);
		break;
	default:
		register_code(KC_LGUI);
		break;
	}
}

void ralt_gui_reset(qk_tap_dance_state_t* state, void* user_data) {
	switch (state->count) {
	case 1:
		layer_off(RALT);
		break;
	default:
		unregister_code(KC_LGUI);
		break;
	}
}

void lalt_shift_finish(qk_tap_dance_state_t* state, void* user_data) {
	switch (state->count) {
	case 1:
		register_code(KC_LALT);
		break;
	case 2:
		register_code(KC_RSFT);
		register_code(KC_LALT);
		break;
	default:
		register_code(KC_LALT);
		register_code(KC_LGUI);
		break;
	}
}

void lalt_shift_reset(qk_tap_dance_state_t* state, void* user_data) {
	switch (state->count) {
	case 1:
		unregister_code(KC_LALT);
		break;
	case 2:
		unregister_code(KC_RSFT);
		unregister_code(KC_LALT);
		break;
	default:
		unregister_code(KC_LALT);
		unregister_code(KC_LGUI);
		break;
	}
}

void shift_gui_finish(qk_tap_dance_state_t* state, void* user_data) {
	switch (state->count) {
	case 1:
		register_code(KC_RSFT);
		break;
	case 2:
		register_code(KC_LGUI);
		break;
	case 3:
		register_code(KC_RSFT);
		register_code(KC_LGUI);
		break;
	default:
		register_code(KC_LALT);
		register_code(KC_RSFT);
		register_code(KC_LGUI);
		break;
	}
}

void shift_gui_reset(qk_tap_dance_state_t* state, void* user_data) {
	switch (state->count) {
	case 1:
		unregister_code(KC_RSFT);
		break;
	case 2:
		unregister_code(KC_LGUI);
		break;
	case 3:
		unregister_code(KC_RSFT);
		unregister_code(KC_LGUI);
		break;
	default:
		unregister_code(KC_LALT);
		unregister_code(KC_RSFT);
		unregister_code(KC_LGUI);
		break;
	}
}

qk_tap_dance_action_t tap_dance_actions[] =
  {
		[UPPER_LOWER_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, upper_lower_finish, upper_lower_reset, 275),
		[RALT_GUI_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ralt_gui_finish, ralt_gui_reset, 275),
		[LALT_SHIFT_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, lalt_shift_finish, lalt_shift_reset, 275),
		[SHIFT_GUI_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, shift_gui_finish, shift_gui_reset, 275)
  };

#define FN_DK2 TD(UPPER_LOWER_MOD)
#define TD_RALT TD(RALT_GUI_MOD)
#define TD_LALT TD(LALT_SHIFT_MOD)
#define TD_RSFT TD(SHIFT_GUI_MOD)

#define FN_LGAL LALT(KC_LGUI)

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
  [BASE] = LAYOUT( \
      KC_QUOT,   KC_COMM,    KC_DOT,      KC_P,      KC_Y,            KC_F,      KC_G,      KC_C,      KC_R,      KC_L,\
         KC_A,      KC_O,      KC_E,      KC_U,      KC_I,            KC_D,      KC_H,      KC_T,      KC_N,      KC_S,\
      KC_SCLN,      KC_Q,      KC_J,      KC_K,      KC_X,            KC_B,      KC_M,      KC_W,      KC_V,      KC_Z,\
                            TD_RALT,   KC_LCTL,    FN_DK2,         TD_LALT,    KC_SPC,   TD_RSFT\
  ),

  [RAISE] = LAYOUT( \
         KC_1,      KC_2,      KC_3,      KC_4,      KC_5,            KC_6,      KC_7,      KC_8,      KC_9,      KC_0,\
       KC_TAB,   KC_COMM,    KC_DOT,   KC_UNDS,   KC_MINS,         KC_PIPE,   KC_SLSH,   KC_PLUS,   KC_QUES,   KC_BSPC,\
       KC_ESC,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,         KC_RCTL,   KC_BSLS,    KC_EQL,   XXXXXXX,    KC_ENT,\
                            KC_LGUI,   KC_LCTL,   XXXXXXX,         TD_LALT,    KC_SPC,   TD_RSFT\
  ),

  [LOWER] = LAYOUT( \
        KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,           KC_F6,     KC_F7,     KC_F8,     KC_F9,    KC_F10,\
      KC_CLCK,   KC_SLCK,   KC_VOLU,   KC_MUTE,    KC_F11,          KC_F12,   XXXXXXX,   KC_PGUP,   XXXXXXX,   XXXXXXX,\
        RESET,   XXXXXXX,   KC_VOLD,   XXXXXXX,   XXXXXXX,         XXXXXXX,   KC_HOME, KC_PGDOWN,    KC_END,    KC_ENT,\
                            KC_LGUI,   KC_LCTL,   XXXXXXX,         TD_LALT,    KC_SPC,   TD_RSFT\
 ),

  [RALT] = LAYOUT( \
    KC_INSERT,    KC_GRV,   KC_TILD,   KC_LBRC,     KC_LT,           KC_GT,   KC_RBRC,    FNRA_C,   XXXXXXX,    FNRA_L,\
       FNRA_A,    FNRA_O,    FNRA_E,   KC_LPRN,   KC_LCBR,         KC_RCBR,   KC_RPRN,     KC_UP,    FNRA_N,    FNRA_S,\
    KC_DELETE,     SUPER,   KC_LSFT,     HYPER,    FNRA_X,         XXXXXXX,   KC_LEFT,   KC_DOWN,  KC_RIGHT,    FNRA_Z,\
                            XXXXXXX,   KC_LCTL,   KC_LGUI,         TD_LALT,    KC_SPC,   TD_RSFT\
  )
};
