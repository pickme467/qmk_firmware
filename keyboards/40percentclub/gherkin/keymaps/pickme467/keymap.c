#include QMK_KEYBOARD_H

enum {
      BASE = 0,
      GAME,
      QWERTY,
      NUMBERS,
      NUMBERS_QWERTY,
      RALTS,
      FUNCTIONS,
      MOUSE,
      SERVICE,
};

enum {
      UPPER_LOWER_MOD = 0,
      UPPER_LOWER_MOD_QWERTY,
};

enum custom_keycodes {
      MC_SU1 = SAFE_RANGE,
      MC_ROOT,
};

#define xstr(s) str(s)
#define str(s) #s

void layer_reset(void) {
  layer_off(NUMBERS);
  layer_off(NUMBERS_QWERTY);
  layer_off(FUNCTIONS);
  layer_off(MOUSE);
  layer_off(SERVICE);
}

void upper_lower_function(tap_dance_state_t* state, void* user_data) {
  if (state->pressed) {
    switch (state->count) {
    case 1:
      layer_on(NUMBERS);
      break;
    case 2:
      layer_on(FUNCTIONS);
      break;
    case 3:
      layer_on(MOUSE);
      break;
    default:
      layer_on(SERVICE);
      break;
    }
  } else {
    layer_reset();
  }
}

void upper_lower_function_qwerty(tap_dance_state_t* state, void* user_data) {
  if (state->pressed) {
    switch (state->count) {
    case 1:
      layer_on(NUMBERS_QWERTY);
      break;
    case 2:
      layer_on(FUNCTIONS);
      break;
    case 3:
      layer_on(MOUSE);
      break;
    default:
      layer_on(SERVICE);
      break;
    }
  } else {
    layer_reset();
  }
}

void upper_lower_reset(tap_dance_state_t* state, void* user_data) {
  layer_reset();
}

tap_dance_action_t tap_dance_actions[] =
  {
   [UPPER_LOWER_MOD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, upper_lower_function, upper_lower_reset),
   [UPPER_LOWER_MOD_QWERTY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, upper_lower_function_qwerty, upper_lower_reset),
  };

#define FN_QUOT MT(MOD_LSFT, KC_QUOT)
#define FN_COMM MT(MOD_LCTL, KC_COMM)
#define FN_DOT MT(MOD_LALT, KC_DOT)
#define FN_P MT(MOD_LGUI, KC_P)
#define FN_G MT(MOD_RGUI, KC_G)
#define FN_C MT(MOD_LALT, KC_C)
#define FN_R MT(MOD_RCTL, KC_R)
#define FN_L MT(MOD_RSFT, KC_L)

#define FN_J LT(RALTS, KC_J)
#define FN_X TD(UPPER_LOWER_MOD)
#define FN_B TD(UPPER_LOWER_MOD_QWERTY)
#define FN_GAME DF(GAME)
#define FN_QWERTY DF(QWERTY)
#define FN_BASE DF(BASE)

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

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // GUI
  case FN_P:
  case FN_G:
		// ALT
  case FN_DOT:
  case FN_C:
    return TAPPING_TERM * 2;
    // CTRL
  case FN_COMM:
  case FN_R:
    return TAPPING_TERM * 12 / 10;
    // TAP DANCE
  case FN_X:
  case FN_B:
    return 275;
  default:
    return TAPPING_TERM;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = LAYOUT_ortho_3x10(
    FN_QUOT,   FN_COMM,    FN_DOT,      FN_P,      KC_Y,      KC_F,      FN_G,      FN_C,      FN_R,      FN_L,
       KC_A,      KC_O,      KC_E,      KC_U,      KC_I,      KC_D,      KC_H,      KC_T,      KC_N,      KC_S,
    KC_SCLN,      KC_Q,      FN_J,      KC_K,      FN_X,    KC_SPC,      KC_M,      KC_W,      KC_V,      KC_Z
  ),

  [NUMBERS] = LAYOUT_ortho_3x10(
    KC_BSLS,   KC_COMM,    KC_DOT,   KC_PIPE,    FN_AST,   KC_QUES,      KC_1,      KC_2,      KC_3,      KC_0,
     KC_TAB,    KC_EQL,   KC_PLUS,   KC_UNDS,   KC_MINS,   KC_SLSH,      KC_4,      KC_5,      KC_6,   KC_BSPC,
     KC_ESC,   XXXXXXX,   XXXXXXX,      KC_X,   XXXXXXX,      KC_B,      KC_7,      KC_8,      KC_9,    KC_ENT
  ),

  [NUMBERS_QWERTY] = LAYOUT_ortho_3x10(
    KC_BSLS,   KC_COMM,    KC_DOT,   KC_PIPE,    FN_AST,   KC_QUES,      KC_1,      KC_2,      KC_3,      KC_0,
     KC_TAB,    KC_EQL,   KC_PLUS,   KC_UNDS,   KC_MINS,   KC_SLSH,      KC_4,      KC_5,      KC_6,   KC_BSPC,
     KC_ESC,   XXXXXXX,   XXXXXXX,      KC_B,   XXXXXXX,      KC_N,      KC_7,      KC_8,      KC_9,    KC_ENT
  ),

  [RALTS] = LAYOUT_ortho_3x10(
  KC_INSERT,    KC_GRV,   KC_TILD,   KC_LBRC,     KC_LT,     KC_GT,   KC_RBRC,    FNRA_C,    XXXXXXX,    FNRA_L,
     FNRA_A,    FNRA_O,    FNRA_E,   KC_LPRN,   KC_LCBR,   KC_RCBR,   KC_RPRN,     KC_UP,     FNRA_N,    FNRA_S,
  KC_DELETE,     SUPER,   XXXXXXX,     HYPER,    FNRA_X,      KC_B,   KC_LEFT,   KC_DOWN,   KC_RIGHT,    FNRA_Z
  ),

  [FUNCTIONS] = LAYOUT_ortho_3x10(
      KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,    KC_F10,
    KC_CAPS,   KC_SCRL,   KC_VOLU,   KC_MUTE,    KC_F11,    KC_F12,   XXXXXXX,   KC_PGUP,   XXXXXXX,   XXXXXXX,
    QK_BOOT,   XXXXXXX,   KC_VOLD,      KC_X,   XXXXXXX,   XXXXXXX,   KC_HOME,   KC_PGDN,    KC_END,    KC_ENT
  ),

  [SERVICE] = LAYOUT_ortho_3x10(
    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX, FN_QWERTY,   FN_GAME,
    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   FN_BASE,
    QK_BOOT,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX
  ),

  [MOUSE] = LAYOUT_ortho_3x10(
    XXXXXXX,   XXXXXXX,   KC_ACL0,   KC_BTN2,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_WH_U,
    XXXXXXX,   XXXXXXX,   KC_ACL1,   KC_BTN1,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_MS_U,   XXXXXXX,   KC_WH_D,
    XXXXXXX,   XXXXXXX,   KC_ACL2,   KC_BTN3,   XXXXXXX,   XXXXXXX,   KC_MS_L,   KC_MS_D,   KC_MS_R,   XXXXXXX
  ),

  [GAME] = LAYOUT_ortho_3x10(
    KC_QUOT,   KC_COMM,    KC_DOT,      KC_P,      KC_Y,      KC_F,      KC_G,      KC_C,      KC_R,      KC_L,
       KC_A,      KC_O,      KC_E,      KC_U,      KC_I,      KC_D,      KC_H,      KC_T,      KC_N,      KC_S,
    KC_SCLN,      KC_Q,      KC_J,      KC_K,      FN_X,    KC_SPC,      KC_M,      KC_W,      KC_V,      KC_Z
  ),

  [QWERTY] = LAYOUT_ortho_3x10(
       KC_Q,      KC_W,     KC_E,       KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,
       KC_A,      KC_S,     KC_D,       KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,   KC_SCLN,
       KC_Z,      KC_X,     KC_C,       KC_V,      FN_B,    KC_SPC,      KC_M,    KC_COMM,    KC_DOT, KC_SLASH
  ),

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
