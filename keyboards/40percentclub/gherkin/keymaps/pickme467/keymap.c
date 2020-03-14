#include QMK_KEYBOARD_H

#define FN_1 LT(1, KC_QUOTE)
#define FN_2 LT(1, KC_COMMA)
#define FN_3 LT(1, KC_DOT)
#define FN_4 LT(1, KC_SCOLON)
#define FN_5 MO(2)
#define FN_L LT(1, KC_L)
#define FN_R LT(1, KC_R)
#define FN_C LT(1, KC_C)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_3x10(
    FN_1,    FN_2,    FN_3,    KC_P,    KC_Y,    KC_F,    KC_G,    FN_C,    FN_R,    FN_L,
    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,
    FN_4,    KC_Q,    KC_J,    KC_K,    KC_X,  KC_SPC,    KC_M,    KC_W,    KC_V,    KC_Z
  ),

  [1] = LAYOUT_ortho_3x10(
     KC_ESC, KC_CAPS, KC_MINS, KC_NUHS,  KC_GRV, KC_SLSH,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSPC,
     KC_TAB, KC_HOME, KC_PGUP, KC_PGDN,  KC_END, KC_LEFT,   KC_UP, KC_DOWN, KC_RIGHT,  KC_ENT,
    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,    FN_5,    KC_B, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT
  ),

  [2] = LAYOUT_ortho_3x10(
       KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
     KC_DEL,  KC_INS, KC_MINS, KC_NUHS,  KC_GRV, KC_SLSH,  KC_EQL, KC_LBRC, KC_RBRC,   RESET,
    KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI, XXXXXXX,  KC_SPC, KC_RGUI, KC_RALT, KC_RCTL, KC_RSFT
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
