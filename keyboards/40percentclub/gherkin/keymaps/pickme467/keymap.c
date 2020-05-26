#include QMK_KEYBOARD_H

enum {
      BASE = 0,
      NUMBERS,
      RALTS,
      FUNCTIONS,
};

enum {
      UPPER_LOWER_MOD = 0,
};

void layer_reset(void) {
  layer_off(NUMBERS);
  layer_off(FUNCTIONS);
}

void upper_lower_function(qk_tap_dance_state_t* state, void* user_data) {
  if (state->pressed) {
    switch (state->count) {
    case 1:
      layer_on(NUMBERS);
      break;
    default:
      layer_on(FUNCTIONS);
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

#define FN_MUTE KC__MUTE
#define FN_VOLU KC__VOLUP
#define FN_VOLD KC__VOLDOWN
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

  [BASE] = LAYOUT_ortho_3x10(
    FN_QUOT,   FN_COMM,    FN_DOT,      FN_P,      KC_Y,      KC_F,      FN_G,      FN_C,      FN_R,      FN_L,
       KC_A,      KC_O,      KC_E,      KC_U,      KC_I,      KC_D,      KC_H,      KC_T,      KC_N,      KC_S,
    KC_SCLN,      KC_Q,      FN_J,      KC_K,      FN_X,    KC_SPC,      KC_M,      KC_W,      KC_V,      KC_Z
  ),

  [NUMBERS] = LAYOUT_ortho_3x10(
       KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,
     KC_TAB,   KC_COMM,    KC_DOT,   KC_UNDS,   KC_MINS,   KC_PIPE,   KC_SLSH,   KC_PLUS,   KC_QUES,   KC_BSPC,
     KC_ESC,   XXXXXXX,    KC_GRV,      KC_X,   XXXXXXX,      KC_B,   KC_BSLS,   KC_TILD,    KC_EQL,    KC_ENT
  ),

  [RALTS] = LAYOUT_ortho_3x10(
    XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_LBRC,     KC_LT,     KC_GT,   KC_RBRC,    FNRA_C,    XXXXXXX,    FNRA_L,
     FNRA_A,    FNRA_O,    FNRA_E,   KC_LPRN,   KC_LCBR,   KC_RCBR,   KC_RPRN,     KC_UP,     FNRA_N,    FNRA_S,
    XXXXXXX,     SUPER,   XXXXXXX,     HYPER,    FNRA_X,      KC_B,   KC_LEFT,   KC_DOWN,   KC_RIGHT,    FNRA_Z
  ),

  [FUNCTIONS] = LAYOUT_ortho_3x10(
      KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,    KC_F10,
  KC_INSERT, KC_DELETE,   FN_VOLU,   FN_MUTE,    KC_F11,    KC_F12,   KC_SLCK,   KC_PGUP,   KC_VOLU,   KC_MUTE,
      RESET,   KC_CLCK,   FN_VOLD,      KC_X,   XXXXXXX,   KC_HOME,    KC_END, KC_PGDOWN,   KC_VOLD,    KC_ENT
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
