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
	default:
		register_code(KC_RSFT);
		register_code(KC_LALT);
		break;
	}
}

void lalt_shift_reset(qk_tap_dance_state_t* state, void* user_data) {
	switch (state->count) {
	case 1:
		unregister_code(KC_LALT);
		break;
	default:
		unregister_code(KC_RSFT);
		unregister_code(KC_LALT);
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
	case 4:
		register_code(KC_LALT);
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
	case 4:
		unregister_code(KC_LALT);
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
  [BASE] = LAYOUT( \
      RGB_HUD,   KC_QUOT,   KC_COMM,    KC_DOT,      KC_P,      KC_Y,             KC_F,      KC_G,      KC_C,      KC_R,      KC_L,   RGB_HUI,\
      RGB_SPD,      KC_A,      KC_O,      KC_E,      KC_U,      KC_I,             KC_D,      KC_H,      KC_T,      KC_N,      KC_S,   RGB_SPI,\
      RGB_SAD,   KC_SCLN,      KC_Q,      KC_J,      KC_K,      KC_X,             KC_B,      KC_M,      KC_W,      KC_V,      KC_Z,   RGB_SAI,\
                                       TD_RALT,   KC_LCTL,    FN_DK2,          TD_LALT,    KC_SPC,   TD_RSFT\
  ),

  [RAISE] = LAYOUT( \
      RGB_VAD,      KC_1,      KC_2,      KC_3,      KC_4,      KC_5,             KC_6,      KC_7,      KC_8,      KC_9,      KC_0,   RGB_VAI,\
     RGB_RMOD,    KC_TAB,   KC_COMM,    KC_DOT,   KC_UNDS,   KC_MINS,          KC_PIPE,   KC_SLSH,   KC_PLUS,   KC_QUES,   KC_BSPC,   RGB_MOD,\
      RGB_TOG,    KC_ESC,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,          KC_RCTL,   KC_BSLS,    KC_EQL,   XXXXXXX,    KC_ENT,   RGB_TOG,\
                                       KC_LGUI,   KC_LCTL,   XXXXXXX,          TD_LALT,    KC_SPC,   TD_RSFT\
  ),

  [LOWER] = LAYOUT( \
      XXXXXXX,     KC_F1,     KC_F2,     KC_F3,     KC_F4,     KC_F5,            KC_F6,     KC_F7,     KC_F8,     KC_F9,    KC_F10,   XXXXXXX,\
      XXXXXXX,   KC_CLCK,   KC_SLCK,   FN_VOLU,   FN_MUTE,    KC_F11,           KC_F12,   XXXXXXX,   KC_PGUP,   XXXXXXX,   XXXXXXX,   XXXXXXX,\
      EEP_RST,     RESET,   XXXXXXX,   FN_VOLD,   XXXXXXX,   XXXXXXX,          XXXXXXX,   KC_HOME, KC_PGDOWN,    KC_END,    KC_ENT,   XXXXXXX,\
                                       KC_LGUI,   KC_LCTL,   XXXXXXX,          TD_LALT,    KC_SPC,   TD_RSFT\
  ),

  [RALT] = LAYOUT( \
      XXXXXXX, KC_INSERT,    KC_GRV,   KC_TILD,   KC_LBRC,     KC_LT,            KC_GT,   KC_RBRC,    FNRA_C,   XXXXXXX,    FNRA_L,   XXXXXXX,\
      XXXXXXX,    FNRA_A,    FNRA_O,    FNRA_E,   KC_LPRN,   KC_LCBR,          KC_RCBR,   KC_RPRN,     KC_UP,    FNRA_N,    FNRA_S,   XXXXXXX,\
      XXXXXXX, KC_DELETE,     SUPER,   KC_LSFT,     HYPER,    FNRA_X,          XXXXXXX,   KC_LEFT,   KC_DOWN,  KC_RIGHT,    FNRA_Z,   XXXXXXX,\
                                       XXXXXXX,   KC_LCTL,   KC_LGUI,          TD_LALT,    KC_SPC,   TD_RSFT\
  )
};

extern uint8_t is_master;

void matrix_init_user(void) {
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
  }
  return true;
}
