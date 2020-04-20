#include QMK_KEYBOARD_H

#define _DVORAK 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 3
#define _POLISH 4

enum {
      LOWER_UPPER_MOD = 0,
      UPPER_LOWER_MOD,
};

void layer_reset(void) {
  layer_off(_LOWER);
  layer_off(_RAISE);
  layer_off(_ADJUST);
}

void lower_upper_finish(qk_tap_dance_state_t* state, void* user_data) {
  if (state->pressed) {
    switch (state->count) {
    case 1:
      layer_on(_LOWER);
      break;
    case 2:
      layer_on(_RAISE);
      break;
    default:
      layer_on(_ADJUST);
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
      layer_on(_RAISE);
      break;
    case 2:
      layer_on(_LOWER);
      break;
    default:
      layer_on(_ADJUST);
       break;
    }
  } else {
    layer_reset();
  }
}

void upper_lower_reset(qk_tap_dance_state_t* state, void* user_data) {
  layer_reset();
}

qk_tap_dance_action_t tap_dance_actions[] =
  {
   [LOWER_UPPER_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, lower_upper_finish, lower_upper_reset, 275),
   [UPPER_LOWER_MOD] = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, upper_lower_finish, upper_lower_reset, 275)
  };

#define FN_DK1 TD(UPPER_LOWER_MOD)
#define FN_DK2 TD(UPPER_LOWER_MOD)
#define FN_LK1 KC_INSERT
#define FN_LK2 KC_RIGHT
#define FN_LK3 KC_PGDOWN
#define FN_LK4 KC_DELETE
#define FN_AK1 KC__MUTE
#define FN_AK2 KC__VOLDOWN
#define FN_AK3 KC__VOLUP
#define FN_RALT MO(_POLISH)
#define FNRA_A RALT(KC_A)
#define FNRA_C RALT(KC_C)
#define FNRA_E RALT(KC_E)
#define FNRA_L RALT(KC_L)
#define FNRA_N RALT(KC_N)
#define FNRA_O RALT(KC_O)
#define FNRA_S RALT(KC_S)
#define FNRA_X RALT(KC_X)
#define FNRA_Z RALT(KC_Z)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_DVORAK] = LAYOUT( \
  //,-----------------------------------------------------.           ,-----------------------------------------------------.
      RGB_HUD, KC_QUOT, KC_COMM,  KC_DOT,    KC_P,    KC_Y,                KC_F,    KC_G,    KC_C,    KC_R,    KC_L, RGB_HUI,\
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
      RGB_SPD,    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                KC_D,    KC_H,    KC_T,    KC_N,    KC_S, RGB_SPI,\
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
      RGB_SAD, KC_SCLN,    KC_Q,    KC_J,    KC_K,    KC_X,                KC_B,    KC_M,    KC_W,    KC_V,    KC_Z, RGB_SAI,\
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
                                 FN_RALT, KC_LCTL,  FN_DK2,             KC_LALT,  KC_SPC, KC_RSFT\
                             //`--------------------------'           `--------------------------'

  ),

  [_LOWER] = LAYOUT( \
  //,-----------------------------------------------------.           ,-----------------------------------------------------.
      XXXXXXX, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,             KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_HOME,  FN_LK3, KC_PGUP,  KC_END, XXXXXXX,             XXXXXXX, KC_LEFT,   KC_UP, KC_DOWN,  FN_LK2, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_CLCK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX,  FN_LK1,  FN_LK4, XXXXXXX,  KC_ENT, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
                                 KC_LGUI, KC_LCTL, XXXXXXX,             KC_LALT, KC_RGUI, KC_RSFT\
                             //`--------------------------'           `--------------------------'
    ),

  [_RAISE] = LAYOUT( \
  //,-----------------------------------------------------.           ,-----------------------------------------------------.
      RGB_VAD,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                KC_6,    KC_7,    KC_8,    KC_9,    KC_0, RGB_VAI,\
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
     RGB_RMOD,  KC_TAB, KC_COMM,  KC_DOT, KC_UNDS, KC_MINS,             KC_SLSH, KC_BSLS, KC_PLUS, KC_QUES, KC_BSPC, RGB_MOD,\
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
      RGB_TOG,  KC_ESC, XXXXXXX,  KC_EQL, XXXXXXX, XXXXXXX,             KC_RCTL, KC_PIPE,  KC_TILD, KC_GRV,  KC_ENT, RGB_TOG,\
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
                                 KC_LGUI, KC_LCTL, XXXXXXX,             KC_LALT, KC_RGUI, KC_RSFT\
                             //`--------------------------'           `--------------------------'
  ),

  [_ADJUST] = LAYOUT( \
  //,-----------------------------------------------------.           ,-----------------------------------------------------.
      XXXXXXX,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,               KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX,  FN_AK1,  FN_AK2,  KC_F11,              KC_F12,  FN_AK3, KC_VOLU, KC_VOLD, KC_MUTE, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
      EEP_RST,   RESET, KC_SLCK, XXXXXXX, XXXXXXX, XXXXXXX,             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
                                 KC_LGUI, KC_LCTL, XXXXXXX,             KC_LALT, KC_RGUI, KC_RSFT\
                             //`--------------------------'           `--------------------------'
  ),

  [_POLISH] = LAYOUT( \
  //,-----------------------------------------------------.           ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LCBR, KC_RCBR,             KC_LBRC, KC_RBRC,  FNRA_C, XXXXXXX,  FNRA_L, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  FNRA_A,  FNRA_O,  FNRA_E,   KC_LT,   KC_GT,             KC_LPRN, KC_RPRN,   KC_UP,  FNRA_N,  FNRA_S, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  FNRA_X,             XXXXXXX, KC_LEFT, KC_DOWN,  FN_LK2,  FNRA_Z, XXXXXXX,\
  //|--------+--------+--------+--------+--------+--------|           |--------+--------+--------+--------+--------+--------|
                                 XXXXXXX, KC_LCTL, KC_LGUI,             KC_LALT,  KC_SPC, KC_RSFT\
                             //`--------------------------'           `--------------------------'

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
