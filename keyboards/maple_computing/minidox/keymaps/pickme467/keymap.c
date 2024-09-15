#include QMK_KEYBOARD_H

enum {
  BASE = 0,
  NUMBERS,
  RALTS,
  FUNCTIONS,
  STRINGS,
};

enum {
  UPPER_LOWER_MOD = 0,
  RALT_GUI_MOD,
  LALT_SHIFT_MOD,
  SHIFT_GUI_MOD,
  CTRL_UPPER_LOWER_MOD,
};

enum custom_keycodes {
      MC_SU1 = SAFE_RANGE,
      MC_ROOT,
};

#define xstr(s) str(s)
#define str(s) #s

void upper_lower_finish(tap_dance_state_t* state, void* user_data) {
  switch (state->count) {
  case 1:
    layer_on(NUMBERS);
    break;
  case 2:
    layer_on(FUNCTIONS);
    break;
  default:
    layer_on(STRINGS);
    break;
  }
}

void upper_lower_reset(tap_dance_state_t* state, void* user_data) {
  switch (state->count) {
  case 1:
    layer_off(NUMBERS);
    break;
  case 2:
    layer_off(FUNCTIONS);
    break;
  default:
    layer_off(STRINGS);
    break;
  }
}

void ctrl_upper_lower_finish(tap_dance_state_t* state, void* user_data) {
  register_code(KC_LCTL);
  switch (state->count) {
  case 1:
    break;
  case 2:
    layer_on(NUMBERS);
    break;
  case 3:
    layer_on(FUNCTIONS);
    break;
  default:
    layer_on(STRINGS);
    break;
  }
}

void ctrl_upper_lower_reset(tap_dance_state_t* state, void* user_data) {
  switch (state->count) {
  case 1:
    break;
  case 2:
    layer_off(NUMBERS);
    break;
  case 3:
    layer_off(FUNCTIONS);
    break;
  default:
    layer_off(STRINGS);
    break;
  }
  unregister_code(KC_LCTL);
}

void ralt_ctrl_gui_finish(tap_dance_state_t* state, void* user_data) {
  switch (state->count) {
  case 1:
    layer_on(RALTS);
    break;
  case 2:
    layer_on(RALTS);
    register_code(KC_LCTL);
    break;
  default:
    register_code(KC_LGUI);
    break;
  }
}

void ralt_ctrl_gui_reset(tap_dance_state_t* state, void* user_data) {
  switch (state->count) {
  case 1:
    layer_off(RALTS);
    break;
  case 2:
    unregister_code(KC_LCTL);
    layer_off(RALTS);
    break;
  default:
    unregister_code(KC_LGUI);
    break;
  }
}

void lalt_shift_finish(tap_dance_state_t* state, void* user_data) {
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

void lalt_shift_reset(tap_dance_state_t* state, void* user_data) {
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

void shift_gui_finish(tap_dance_state_t* state, void* user_data) {
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

void shift_gui_reset(tap_dance_state_t* state, void* user_data) {
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

tap_dance_action_t tap_dance_actions[] =
  {
    [UPPER_LOWER_MOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, upper_lower_finish, upper_lower_reset),
    [RALT_GUI_MOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ralt_ctrl_gui_finish, ralt_ctrl_gui_reset),
    [LALT_SHIFT_MOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lalt_shift_finish, lalt_shift_reset),
    [SHIFT_GUI_MOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, shift_gui_finish, shift_gui_reset),
    [CTRL_UPPER_LOWER_MOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrl_upper_lower_finish, ctrl_upper_lower_reset)
  };

#define TD_LAYR TD(UPPER_LOWER_MOD)
#define TD_RALT TD(RALT_GUI_MOD)
#define TD_LALT TD(LALT_SHIFT_MOD)
#define TD_RSFT TD(SHIFT_GUI_MOD)
#define TD_LCTL TD(CTRL_UPPER_LOWER_MOD)

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

#define FN_AST LSFT(KC_8)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT( \
      KC_QUOT,   KC_COMM,    KC_DOT,      KC_P,      KC_Y,            KC_F,      KC_G,      KC_C,      KC_R,      KC_L,\
         KC_A,      KC_O,      KC_E,      KC_U,      KC_I,            KC_D,      KC_H,      KC_T,      KC_N,      KC_S,\
      KC_SCLN,      KC_Q,      KC_J,      KC_K,      KC_X,            KC_B,      KC_M,      KC_W,      KC_V,      KC_Z,\
                            TD_RALT,   TD_LCTL,   TD_LAYR,         TD_LALT,    KC_SPC,   TD_RSFT\
  ),

  [NUMBERS] = LAYOUT( \
      KC_BSLS,   KC_COMM,    KC_DOT,   KC_PIPE,    FN_AST,         KC_QUES,      KC_1,      KC_2,      KC_3,      KC_0,\
       KC_TAB,    KC_EQL,   KC_PLUS,   KC_UNDS,   KC_MINS,         KC_SLSH,      KC_4,      KC_5,      KC_6,   KC_BSPC,\
       KC_ESC,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,         KC_RCTL,      KC_7,      KC_8,      KC_9,    KC_ENT,\
                            XXXXXXX,   XXXXXXX,   XXXXXXX,         TD_LALT,    KC_SPC,   TD_RSFT\
  ),

  [FUNCTIONS] = LAYOUT( \
      XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,         XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,\
      KC_CAPS,   KC_SCRL,   XXXXXXX,   XXXXXXX,   XXXXXXX,         XXXXXXX,   XXXXXXX,   KC_PGUP,   XXXXXXX,   XXXXXXX,\
      QK_BOOT,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,         XXXXXXX,   KC_HOME,   KC_PGDN,    KC_END,    KC_ENT,\
                            XXXXXXX,   XXXXXXX,   XXXXXXX,         TD_LALT,    KC_SPC,   TD_RSFT\
  ),

  [RALTS] = LAYOUT( \
    KC_INSERT,    KC_GRV,   KC_TILD,   KC_LBRC,     KC_LT,           KC_GT,   KC_RBRC,    FNRA_C,   XXXXXXX,    FNRA_L,\
       FNRA_A,    FNRA_O,    FNRA_E,   KC_LPRN,   KC_LCBR,         KC_RCBR,   KC_RPRN,     KC_UP,    FNRA_N,    FNRA_S,\
    KC_DELETE,     SUPER,   KC_LSFT,     HYPER,    FNRA_X,         XXXXXXX,   KC_LEFT,   KC_DOWN,  KC_RIGHT,    FNRA_Z,\
                            XXXXXXX,   XXXXXXX,   XXXXXXX,         TD_LALT,    KC_SPC,   TD_RSFT\
  ),

  [STRINGS] = LAYOUT( \
        KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,           KC_F6,     KC_F7,     KC_F8,     KC_F9,    KC_F10,\
    XXXXXXX,   XXXXXXX,   KC_VOLU,     KC_MUTE,    KC_F11,          KC_F12,    MC_SU1,   XXXXXXX,   XXXXXXX,   XXXXXXX, \
    XXXXXXX,   XXXXXXX,   KC_VOLD,     XXXXXXX,   XXXXXXX,         XXXXXXX,   MC_ROOT,   XXXXXXX,   XXXXXXX,   XXXXXXX,\
                            XXXXXXX,   XXXXXXX,   XXXXXXX,         XXXXXXX,   XXXXXXX,   XXXXXXX\
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
    case MC_SU1:
      SEND_STRING(xstr(D_SU1)SS_TAP(X_ENT));
      break;
    case MC_ROOT:
      SEND_STRING(xstr(D_ROOT)SS_TAP(X_ENT));
      break;
    default:
      break;
    }
  }
  return true;
}
