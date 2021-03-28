#include QMK_KEYBOARD_H

enum {
      BASE = 0,
      NUMBERS,
      RALTS,
      FUNCTIONS,
};

enum {
      LOWER_UPPER_MOD = 0,
      UPPER_LOWER_MOD,
      ALT_GUI_MOD
};

void layer_reset(void) {
  layer_off(NUMBERS);
  layer_off(FUNCTIONS);
}

void lower_upper_finish(qk_tap_dance_state_t* state, void* user_data) {
  if (state->pressed) {
    switch (state->count) {
    case 1:
      layer_on(FUNCTIONS);
      break;
    default:
      layer_on(NUMBERS);
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
      layer_on(NUMBERS);
      break;
    default:
      layer_on(FUNCTIONS);
      break;
    }
  } else {
    layer_reset();
  }
}

void upper_lower_reset(qk_tap_dance_state_t* state, void* user_data) {
  layer_reset();
}

void alt_gui_reset(qk_tap_dance_state_t* state, void* user_data) {
  switch(state->count) {
  case 1:
    unregister_code(KC_LALT);
    break;
  default:
    unregister_code(KC_LGUI);
    break;
  }
}

void alt_gui_finish(qk_tap_dance_state_t* state, void* user_data) {
  if (state->pressed) {
    switch (state->count) {
    case 1:
      register_code(KC_LALT);
      break;
    default:
      register_code(KC_LGUI);
      break;
    }
  }
}

qk_tap_dance_action_t tap_dance_actions[] =
  {
   [LOWER_UPPER_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, lower_upper_finish, lower_upper_reset, 275),
   [UPPER_LOWER_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, upper_lower_finish, upper_lower_reset, 275),
   [ALT_GUI_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, alt_gui_finish, alt_gui_reset, 275)
  };

#define FN_DK1 TD(UPPER_LOWER_MOD)
#define FN_DK2 TD(UPPER_LOWER_MOD)
#define FN_LALT TD(ALT_GUI_MOD)

#define FN_RALT MO(RALTS)
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
  [BASE] = LAYOUT_plaid_grid(
    KC_QUOT,   KC_COMM,    KC_DOT,      KC_P,      KC_Y,   XXXXXXX,   XXXXXXX,      KC_F,      KC_G,      KC_C,      KC_R,      KC_L,
       KC_A,      KC_O,      KC_E,      KC_U,      KC_I,   XXXXXXX,   XXXXXXX,      KC_D,      KC_H,      KC_T,      KC_N,      KC_S,
    KC_SCLN,      KC_Q,      KC_J,      KC_K,      KC_X,   XXXXXXX,   XXXXXXX,      KC_B,      KC_M,      KC_W,      KC_V,      KC_Z,
    XXXXXXX,   XXXXXXX,   FN_RALT,   KC_LCTL,    FN_DK2,   XXXXXXX,   XXXXXXX,   KC_LALT,    KC_SPC,   KC_RSFT,   XXXXXXX,   XXXXXXX
  ),

  [NUMBERS] = LAYOUT_plaid_grid(
       KC_1,      KC_2,      KC_3,      KC_4,      KC_5,   XXXXXXX,   XXXXXXX,      KC_6,      KC_7,      KC_8,      KC_9,      KC_0,
     KC_TAB,   KC_COMM,    KC_DOT,   KC_UNDS,   KC_MINS,   XXXXXXX,   XXXXXXX,   KC_PIPE,   KC_SLSH,   KC_PLUS,   KC_QUES,   KC_BSPC,
     KC_ESC,   XXXXXXX,   XXXXXXX,      KC_X,   XXXXXXX,   XXXXXXX,   XXXXXXX,      KC_B,   KC_BSLS,    KC_EQL,   XXXXXXX,    KC_ENT,
    XXXXXXX,   XXXXXXX,   KC_LGUI,   KC_LCTL,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_LGUI,    KC_SPC,   KC_RSFT,   XXXXXXX,   XXXXXXX
  ),

  [FUNCTIONS] = LAYOUT_plaid_grid(
      KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,   XXXXXXX,   XXXXXXX,     KC_F6,     KC_F7,     KC_F8,     KC_F9,    KC_F10,
    KC_CLCK,   KC_SLCK,   KC_VOLU,   KC_MUTE,    KC_F11,   XXXXXXX,   XXXXXXX,    KC_F12,   XXXXXXX,   KC_PGUP,   XXXXXXX,   XXXXXXX,
      RESET,   XXXXXXX,   KC_VOLD,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_HOME, KC_PGDOWN,    KC_END,    KC_ENT,
    XXXXXXX,   XXXXXXX,   KC_LGUI,   KC_LCTL,   XXXXXXX,   XXXXXXX,   XXXXXXX,   FN_LGAL,    KC_SPC,   KC_RSFT,   XXXXXXX,   XXXXXXX
  ),

  [RALTS] = LAYOUT_plaid_grid(
  KC_INSERT,    KC_GRV,   KC_TILD,   KC_LBRC,     KC_LT,   XXXXXXX,   XXXXXXX,     KC_GT,   KC_RBRC,    FNRA_C,    XXXXXXX,    FNRA_L,
     FNRA_A,    FNRA_O,    FNRA_E,   KC_LPRN,   KC_LCBR,   XXXXXXX,   XXXXXXX,   KC_RCBR,   KC_RPRN,     KC_UP,     FNRA_N,    FNRA_S,
  KC_DELETE,     SUPER,   KC_LSFT,     HYPER,    FNRA_X,   XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_LEFT,   KC_DOWN,   KC_RIGHT,    FNRA_Z,
    XXXXXXX,   XXXXXXX,   XXXXXXX,   KC_LCTL,   KC_LGUI,   XXXXXXX,   XXXXXXX,   FN_LALT,    KC_SPC,   KC_RSFT,    XXXXXXX,   XXXXXXX
  )
};

//Setup consts for LED modes
#define LEDMODE_ON 1 //always on
#define LEDMODE_OFF 0 //always off
#define LEDMODE_MODS 2 //On with modifiers
#define LEDMODE_BLINKIN 3 //blinkinlights - % chance toggle on keypress
#define LEDMODE_KEY 4 //On with any keypress, off with key release
#define LEDMODE_ENTER 5 // On with enter key

//Setup config struct for LED
typedef union {
  uint32_t raw;
  struct {
    uint8_t  red_mode :8;
    uint8_t  green_mode :8;
  };
} led_config_t;
led_config_t led_config;

//Set leds to saved state during powerup
void keyboard_post_init_user(void) {
  // set LED pin modes
  //  setPinOutput(LED_RED);
  setPinOutput(LED_GREEN);

  // Call the post init code.
  led_config.raw = eeconfig_read_user();

  led_config.raw = 0;
  led_config.red_mode = LEDMODE_MODS;
  led_config.green_mode = LEDMODE_KEY;

  if(led_config.red_mode == LEDMODE_ON) {
      writePinHigh(LED_RED);
  }

  if(led_config.green_mode == LEDMODE_ON) {
      writePinHigh(LED_GREEN);
  }
}

void eeconfig_init_user(void) {  // EEPROM is getting reset!
  led_config.raw = 0;
  led_config.red_mode = LEDMODE_KEY;
  led_config.green_mode = LEDMODE_OFF;
      eeconfig_update_user(led_config.raw);
  eeconfig_update_user(led_config.raw);
}

// array of keys considered modifiers for led purposes
const uint16_t modifiers[] = {
    KC_LCTL,
    KC_RCTL,
    KC_LALT,
    KC_RALT,
    KC_LSFT,
    KC_RSFT,
    KC_LGUI,
    KC_RGUI,
    FN_DK2,
    FN_RALT,
    FN_LALT
};


void led_keypress_update(uint8_t led, uint8_t led_mode, uint16_t keycode, keyrecord_t *record) {
    switch (led_mode) {
      case LEDMODE_MODS:
        for (int i=0;i<sizeof(modifiers) / sizeof(modifiers[0]);i++) {
          if(keycode==modifiers[i]) {
            if (record->event.pressed) {
              writePinHigh(led);
            }
            else {
              writePinLow(led);
            }
          }
        }
        break;
      case LEDMODE_BLINKIN:
        if (record->event.pressed) {
          if(rand() % 2 == 1) {
            if(rand() % 2 == 0) {
              writePinLow(led);
            }
            else {
              writePinHigh(led);
            }
          }
        }
        break;
      case LEDMODE_KEY:
        if (record->event.pressed) {
          writePinHigh(led);
          return;
        }
        else {
          writePinLow(led);
          return;
        }
        break;
      case LEDMODE_ENTER:
        if (keycode==KC_ENT) {
          writePinHigh(led);
        }
        else {
          writePinLow(led);
        }
        break;

    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  /* If the either led mode is keypressed based, call the led updater
     then let it fall through the keypress handlers. Just to keep
     the logic out of this procedure */
  if (led_config.red_mode >= LEDMODE_MODS && led_config.red_mode <= LEDMODE_ENTER) {
      led_keypress_update(LED_RED, led_config.red_mode, keycode, record);
  }
  if (led_config.green_mode >= LEDMODE_MODS && led_config.green_mode <= LEDMODE_ENTER) {
      led_keypress_update(LED_GREEN, led_config.green_mode, keycode, record);
  }
  return true;
}
