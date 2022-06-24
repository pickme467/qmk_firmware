#include QMK_KEYBOARD_H

enum {
      BASE = 0,
      NUMBERS,
      RALTS,
      SWITCHES,
      EXTRA,
};

enum {
      UPPER_LOWER_MOD = 0,
};

enum custom_keycodes {
      MC_SU1 = SAFE_RANGE,
      MC_ROOT,
};

#define xstr(s) str(s)
#define str(s) #s

void layer_reset(void) {
  layer_off(NUMBERS);
  layer_off(SWITCHES);
  layer_off(EXTRA);
}

void upper_lower_function(qk_tap_dance_state_t* state, void* user_data) {
  if (state->pressed) {
    switch (state->count) {
    case 1:
      layer_on(NUMBERS);
      break;
    case 2:
      layer_on(SWITCHES);
      break;
    default:
      layer_on(EXTRA);
      break;
    }
  } else {
    layer_reset();
    if (state->count == 1) {
      register_code(KC_X);
      unregister_code(KC_X);
    }
  }
}

void upper_lower_reset(qk_tap_dance_state_t* state, void* user_data) {
  layer_reset();
}

qk_tap_dance_action_t tap_dance_actions[] =
  {
   [UPPER_LOWER_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, upper_lower_function, upper_lower_reset, 275),
  };

#define FN_J LT(RALTS, KC_J)
#define FN_X TD(UPPER_LOWER_MOD)

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

  [BASE] = LAYOUT_ortho_3x10(
    KC_QUOT,   KC_COMM,    KC_DOT,      KC_P,      KC_Y,      KC_F,      KC_G,      KC_C,      KC_R,      KC_L,
       KC_A,      KC_O,      KC_E,      KC_U,      KC_I,      KC_D,      KC_H,      KC_T,      KC_N,      KC_S,
    KC_SCLN,      KC_Q,      FN_J,      KC_K,      FN_X,    KC_SPC,      KC_M,      KC_W,      KC_V,      KC_Z
  ),

  [NUMBERS] = LAYOUT_ortho_3x10(
    KC_BSLS,   KC_COMM,    KC_DOT,   KC_PIPE,    FN_AST,   KC_QUES,      KC_1,      KC_2,      KC_3,      KC_0,
     KC_TAB,    KC_EQL,   KC_PLUS,   KC_UNDS,   KC_MINS,   KC_SLSH,      KC_4,      KC_5,      KC_6,   KC_BSPC,
     KC_ESC,   XXXXXXX,   XXXXXXX,      KC_X,   XXXXXXX,      KC_B,      KC_7,      KC_8,      KC_9,    KC_ENT
  ),

  [RALTS] = LAYOUT_ortho_3x10(
  KC_INSERT,    KC_GRV,   KC_TILD,   KC_LBRC,     KC_LT,     KC_GT,   KC_RBRC,    FNRA_C,    XXXXXXX,    FNRA_L,
     FNRA_A,    FNRA_O,    FNRA_E,   KC_LPRN,   KC_LCBR,   KC_RCBR,   KC_RPRN,     KC_UP,     FNRA_N,    FNRA_S,
  KC_DELETE,     SUPER,   XXXXXXX,     HYPER,    FNRA_X,      KC_B,   KC_LEFT,   KC_DOWN,   KC_RIGHT,    FNRA_Z
  ),

  [SWITCHES] = LAYOUT_ortho_3x10(
    KC_LSFT,   KC_LCTL,   KC_LALT,   KC_LGUI,   XXXXXXX,   XXXXXXX,   KC_RGUI,   KC_LALT,   KC_RCTL,   KC_RSFT,
    KC_CLCK,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_PGUP,   XXXXXXX,   KC_BSPC,
    XXXXXXX,   XXXXXXX,   XXXXXXX,      KC_X,   XXXXXXX,      KC_B,   KC_HOME, KC_PGDOWN,    KC_END,    KC_ENT
  ),

  [EXTRA] = LAYOUT_ortho_3x10(
      KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,    KC_F10,
    XXXXXXX,   KC_SLCK,   KC_VOLU,   KC_MUTE,    KC_F11,    KC_F12,    MC_SU1,   XXXXXXX,   XXXXXXX,   XXXXXXX,
      RESET,   XXXXXXX,   KC_VOLD,   XXXXXXX,   XXXXXXX,   XXXXXXX,   MC_ROOT,   XXXXXXX,   XXXXXXX,   XXXXXXX
  ),

};

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(D5);
  setPinOutput(B0);
}

void led_set_user(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
    writePinLow(D5);
  } else {
    writePinHigh(D5);
  }

  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinLow(B0);
  } else {
    writePinHigh(B0);
  }
}

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
