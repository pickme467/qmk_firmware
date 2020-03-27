#include QMK_KEYBOARD_H

enum {
      MAIN = 0,
      CURSORS,
      NUMBERS,
      BRACES,
      FUNCTIONS,
};

enum {
      UPPER_LOWER_MOD = 0,
};

void layer_reset(void) {
  layer_off(CURSORS);
  layer_off(NUMBERS);
  layer_off(FUNCTIONS);
}

void upper_lower_function(qk_tap_dance_state_t* state, void* user_data) {
  if (state->pressed) {
    switch (state->count) {
    case 1:
      layer_on(NUMBERS);
      break;
    case 2:
      layer_on(CURSORS);
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

#define FN_MUTE KC__MUTE
#define FN_VOLU KC__VOLUP
#define FN_VOLD KC__VOLDOWN

#define FN_QUOT MT(MOD_LSFT, KC_QUOT)
#define FN_COMM MT(MOD_LCTL, KC_COMM)
#define FN_DOT MT(MOD_LALT, KC_DOT)
#define FN_P MT(MOD_LGUI, KC_P)
#define FN_G MT(MOD_RGUI, KC_G)
#define FN_C MT(MOD_LALT, KC_C)
#define FN_R MT(MOD_RCTL, KC_R)
#define FN_L MT(MOD_RSFT, KC_L)

#define FN_U MT(MOD_RALT, KC_U)
#define FN_X TD(UPPER_LOWER_MOD)
#define FN_B KC_SPC

#define FNN_J MO(BRACES)
#define FNN_M MO(BRACES)
#define FN_SPC KC_B

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [MAIN] = LAYOUT_ortho_3x10(
    FN_QUOT,   FN_COMM,    FN_DOT,      FN_P,      KC_Y,      KC_F,      FN_G,      FN_C,      FN_R,      FN_L,
       KC_A,      KC_O,      KC_E,      FN_U,      KC_I,      KC_D,      KC_H,      KC_T,      KC_N,      KC_S,
    KC_SCLN,      KC_Q,      KC_J,      KC_K,      FN_X,      FN_B,      KC_M,      KC_W,      KC_V,      KC_Z
  ),

  [CURSORS] = LAYOUT_ortho_3x10(
    KC_EXLM,     KC_AT,   KC_HASH,    KC_DLR,   KC_PERC,   KC_CIRC,   KC_AMPR,   KC_ASTR,    XXXXXXX,   KC_CLCK,
    KC_HOME, KC_PGDOWN,   KC_PGUP,    KC_END,   KC_COMM,    KC_DOT,   KC_LEFT,     KC_UP,    KC_DOWN,  KC_RIGHT,
    KC_LSFT,   KC_LALT,   KC_LCTL,    KC_LGUI,  XXXXXXX,    FN_SPC,   KC_RGUI,   KC_RCTL,    KC_LALT,   KC_RSFT
  ),

  [NUMBERS] = LAYOUT_ortho_3x10(
       KC_1,      KC_2,      KC_3,      KC_4,      KC_5,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,
     KC_TAB,   XXXXXXX,    KC_EQL,   KC_UNDS,   KC_MINS,   KC_SLSH,   KC_BSLS,   KC_PLUS,   KC_QUES,   KC_BSPC,
     KC_ESC,   XXXXXXX,     FNN_J,      KC_X,   XXXXXXX,    FN_SPC,      FNN_M,   KC_TILD,    KC_GRV,    KC_ENT
  ),

  [BRACES] = LAYOUT_ortho_3x10(
    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_LBRC,   KC_RBRC,    KC_INS,
     KC_TAB,   XXXXXXX,   XXXXXXX,     KC_LT,     KC_GT,   XXXXXXX,   XXXXXXX,   KC_LPRN,   KC_RPRN, KC_DELETE,
    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,    FN_SPC,   XXXXXXX,   KC_LCBR,   KC_RCBR,   KC_PIPE
  ),

  [FUNCTIONS] = LAYOUT_ortho_3x10(
      KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,     KC_F6,     KC_F7,     KC_F8,     KC_F9,    KC_F10,
      RESET,   KC_SLCK,   FN_MUTE,   FN_VOLD,    KC_F11,    KC_F12,   FN_VOLU,   KC_VOLU,   KC_VOLD,   KC_MUTE,
     KC_ESC,   XXXXXXX,   XXXXXXX,      KC_X,   XXXXXXX,    FN_SPC,   XXXXXXX,   XXXXXXX,   XXXXXXX,    KC_ENT
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
