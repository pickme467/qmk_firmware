#include QMK_KEYBOARD_H

enum {
  BASE = 0,
  NUMBERS,
  RALTS,
  FUNCTIONS,
};

enum {
  UPPER_LOWER_MOD = 0,
  RALT_GUI_MOD,
  LALT_SHIFT_MOD,
  SHIFT_GUI_MOD,
  CTRL_UPPER_LOWER_MOD,
};

enum my_keycodes {
	KCM_PAR = SAFE_RANGE
};

void layer_reset(void) {
  layer_off(NUMBERS);
  layer_off(FUNCTIONS);
}

void upper_lower_finish(qk_tap_dance_state_t* state, void* user_data) {
  switch (state->count) {
  case 1:
    layer_on(NUMBERS);
    break;
  default:
    layer_on(FUNCTIONS);
    break;
  }
}

void upper_lower_reset(qk_tap_dance_state_t* state, void* user_data) {
  layer_reset();
}

void ctrl_upper_lower_finish(qk_tap_dance_state_t* state, void* user_data) {
  register_code(KC_LCTL);
  switch (state->count) {
  case 1:
    break;
  case 2:
    layer_on(NUMBERS);
    break;
  default:
    layer_on(FUNCTIONS);
    break;
  }
}

void ctrl_upper_lower_reset(qk_tap_dance_state_t* state, void* user_data) {
  layer_reset();
  unregister_code(KC_LCTL);
}

void ralt_ctrl_gui_finish(qk_tap_dance_state_t* state, void* user_data) {
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

void ralt_ctrl_gui_reset(qk_tap_dance_state_t* state, void* user_data) {
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
    [RALT_GUI_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ralt_ctrl_gui_finish, ralt_ctrl_gui_reset, 275),
    [LALT_SHIFT_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, lalt_shift_finish, lalt_shift_reset, 275),
    [SHIFT_GUI_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, shift_gui_finish, shift_gui_reset, 275),
    [CTRL_UPPER_LOWER_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, ctrl_upper_lower_finish, ctrl_upper_lower_reset, 275)
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT( \
      RGB_HUD,      KC_Q,      KC_W,      KC_E,      KC_R,      KC_T,             KC_Y,      KC_U,      KC_I,    KC_O,      KC_P,   RGB_HUI,\
      RGB_SPD,      KC_A,      KC_S,      KC_D,      KC_F,      KC_G,             KC_H,      KC_J,      KC_K,    KC_L,   KC_SCLN,   RGB_SPI,\
      RGB_SAD,      KC_Z,      KC_X,      KC_C,      KC_V,      KC_B,             KC_N,      KC_M,   KC_COMM,  KC_DOT,   KC_SLSH,   RGB_SAI,\
                                       TD_RSFT,    KC_SPC,   TD_LALT,          TD_LAYR,   TD_LCTL,   TD_RALT\
  ),

  [NUMBERS] = LAYOUT( \
      RGB_VAD,    KC_TAB,   KC_BSLS,    KC_GRV,   KC_PLUS,   KC_LBRC,          KC_RBRC,   KC_MINS,   XXXXXXX,   XXXXXXX,   KC_BSPC,   RGB_VAI,\
     RGB_RMOD,      KC_1,      KC_2,      KC_3,      KC_4,      KC_5,             KC_6,      KC_7,      KC_8,      KC_9,      KC_0,   RGB_MOD,\
      RGB_TOG,    KC_ESC,   KC_PIPE,   KC_TILD,    KC_EQL,   KC_LCBR,          KC_RCBR,   KC_UNDS,   KC_COMM,    KC_DOT,    KC_ENT,   RGB_TOG,\
                                       TD_RSFT,    KC_SPC,   TD_LALT,          XXXXXXX,   XXXXXXX,   XXXXXXX\
  ),

  [FUNCTIONS] = LAYOUT( \
      XXXXXXX,     KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,            KC_F6,     KC_F7,     KC_F8,     KC_F9,    KC_F10,   XXXXXXX,\
      XXXXXXX,   KC_CLCK,   KC_SLCK,   KC_VOLU,   KC_MUTE,    KC_F11,           KC_F12,   XXXXXXX,   KC_PGUP,   XXXXXXX,   XXXXXXX,   XXXXXXX,\
      EEP_RST,     RESET,   XXXXXXX,   KC_VOLD,   XXXXXXX,   XXXXXXX,          XXXXXXX,   KC_HOME, KC_PGDOWN,    KC_END,   XXXXXXX,   XXXXXXX,\
                                       TD_RSFT,    KC_SPC,   TD_LALT,          XXXXXXX,   XXXXXXX,   XXXXXXX\
  ),

  [RALTS] = LAYOUT( \
      XXXXXXX,   XXXXXXX,   XXXXXXX,    FNRA_E,   XXXXXXX,   XXXXXXX,          XXXXXXX,   XXXXXXX,   XXXXXXX,    FNRA_O, KC_DELETE,   XXXXXXX,\
      XXXXXXX,    FNRA_A,    FNRA_S,   XXXXXXX,   KCM_PAR,   XXXXXXX,          XXXXXXX,   XXXXXXX,     KC_UP,    FNRA_L,   KC_QUOT,   XXXXXXX, \
      XXXXXXX,    FNRA_Z,    FNRA_X,    FNRA_C,   XXXXXXX,   XXXXXXX,           FNRA_N,   KC_LEFT,   KC_DOWN,  KC_RIGHT, KC_INSERT,   XXXXXXX,\
                                       TD_RSFT,    KC_SPC,   TD_LALT,          XXXXXXX,   XXXXXXX,   XXXXXXX\
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_NUMBER 2
#define L_RALTS 4
#define L_FUNCTIONS 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_NUMBER:
            oled_write_ln_P(PSTR("Number"), false);
            break;
        case L_RALTS:
            oled_write_ln_P(PSTR("Ralts"), false);
            break;
        case L_FUNCTIONS:
            oled_write_ln_P(PSTR("Functions"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Other"), false);
            break;
    }
}

char keylog_str[24] = {};

void oled_task_user(void) {
  oled_render_layer_state();
}

uint8_t step = 0;
uint8_t old_step = 0;

#include<transactions.h>

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if ((record->event.pressed) && (keycode == KCM_PAR)) {
    register_code(KC_LALT);
    register_code(KC_6);
    unregister_code(KC_6);
    unregister_code(KC_LALT);
  }
  return true;
}

void housekeeping_task_user(void) {
  if (is_keyboard_master()) {
    transaction_rpc_send(ADAM_SEKS, sizeof(step), &step);
  }
}

void user_adam_seks(uint8_t in_len, const void* in_data, uint8_t out_len, void* out_data) {
  old_step = step;
  step = *(uint8_t*)in_data;
}

void keyboard_post_init_user(void) {
  transaction_register_rpc(ADAM_SEKS, user_adam_seks);
}

#endif // OLED_ENABLE
