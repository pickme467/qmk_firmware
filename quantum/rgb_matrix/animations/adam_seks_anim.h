#ifdef ENABLE_RGB_MATRIX_ADAM_SEKS
RGB_MATRIX_EFFECT(ADAM_SEKS)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

extern uint8_t step;
extern uint8_t old_step;
//                      A   D   A   M   S   E   K   S
const uint8_t text[] = {22, 16, 22, 39, 19, 17, 43, 19};

static void print_text(uint8_t i, uint16_t time, effect_params_t* params) {
    HSV hsv = rgb_matrix_config.hsv;
    hsv.v = scale8(abs8(sin8(time) - 128) * 2, hsv.v);
    RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
    rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
}

bool ADAM_SEKS(effect_params_t* params) {
    uint16_t time = scale16by8(g_rgb_timer, rgb_matrix_config.speed / 8);
    if (!params->init) {
      rgb_matrix_set_color_all(0, 0, 0);
      print_text(text[step], time, params);
      if (is_keyboard_master()) {
        if (time % 100 == 0) {
          step++;
          if(step > sizeof(text)) step = 0;
        }
      }
      return false;
    }

    if (old_step != step) {
      rgb_matrix_set_color(text[old_step], 0, 0, 0);
      old_step = step;
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (int i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        print_text(i, time, params);
    }
    return led_max < DRIVER_LED_TOTAL;
}

#    endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif      // DISABLE_RGB_MATRIX_ADAM_SEKS
