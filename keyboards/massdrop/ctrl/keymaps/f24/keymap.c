#include "keymap.h"


static uint16_t idle_timer;         // Idle LED timeout timer
static uint8_t idle_second_counter; // Idle LED seconds counter, counts seconds not milliseconds
static uint8_t key_event_counter;   // This counter is used to check if any keys are being held

static const char * sendstring_commands[] = {
    "RGB TIMEOUT ON ",
    "RGB TIMOUT OFF "
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_SLCK, KC_PAUS,
        KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_INS, KC_HOME, KC_PGUP,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL, KC_END, KC_PGDN,
        MO(2), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_APP, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
    [1] = LAYOUT(
        _______, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, RGB_M_K, RGB_M_X, RGB_M_G, _______, _______, _______, _______,        KC_MUTE, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPLY, KC_MSTP, KC_VOLU,
        _______, RGB_SPD, RGB_VAI, RGB_SPI, RGB_HUI, RGB_SAI, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_MNXT, KC_VOLD,
        _______, RGB_RMOD, RGB_VAD, RGB_MOD, RGB_HUD, RGB_SAD, _______, _______, _______, _______, _______, _______, _______,
        _______, RGB_TOG, BL_STEP, _______, _______, MD_BOOT, NK_TOGG, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

    [2] = LAYOUT(
        DBG_PRNT, KC_F13, KC_F14, KC_F15, KC_F16, KC_F17, KC_F18, KC_F19, KC_F20, KC_F21, KC_F22, KC_F23, KC_F24,                      _______, _______, _______,
        ROUT_TG, LCAS_1, LCAS_2, LCAS_3, LCAS_4, LCAS_5, LCAS_6, LCAS_7, LCAS_8, LCAS_9, _______, _______, _______, _______, _______, _______, _______,
        WIN_PK , _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, WCS_H, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                            _______,
        _______, _______, _______, _______, _______, _______, _______, _______,                                                       _______, _______, _______),

};

#ifdef _______
#undef _______
#define _______ {0, 0, 0}

const uint8_t PROGMEM ledmap[][DRIVER_LED_TOTAL][3] = {
    [0] = {
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                              _______,
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______
    },
 [1] = {
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   PURPLE,  _______,   WHITE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,   WHITE,    WHITE,    WHITE,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                              _______,
        _______, _______, _______,                   _______,                            _______, _______, _______, _______,            _______, _______, _______
    }, [2] = {
        ACTIVE,  ACTIVE,  ACTIVE,  ACTIVE,  ACTIVE,  ACTIVE,   ACTIVE,   ACTIVE, ACTIVE, ACTIVE,   ACTIVE, ACTIVE,  ACTIVE,           _______,    _______,   _______,
        ACTIVE,  ACTIVE, ACTIVE,    ACTIVE,    ACTIVE,    ACTIVE,    ACTIVE, ACTIVE, ACTIVE, ACTIVE,   _______,   _______,   _______,   _______, _______,    _______,   _______,
        _______, _______,  _______,  _______,  _______,  _______,  _______, _______,   _______,   _______, _______, _______, _______, _______, _______,    _______,   _______,
        _______, _______,  _______,  _______,  _______,  _______,  _______, _______, _______, _______, _______, _______, _______,
        _______, _______,  _______, _______,   _______, _______,   _______,   _______, _______, _______, _______, _______,                              _______,
        _______, _______, _______,                   _______,                            _______, _______,    _______, _______,            _______, _______, _______
    },
};

#undef _______
#define _______ KC_TRNS
#endif

#define MODS_SHIFT (get_mods() & MOD_MASK_SHIFT)
#define MODS_CTRL (get_mods() & MOD_MASK_CTRL)
#define MODS_ALT (get_mods() & MOD_MASK_ALT)


bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    static uint32_t key_timer;

    if (record->event.pressed)
    {
        key_event_counter++;
    }
    else
    {
        key_event_counter--;
    }

    if (rgb_time_out_enable)
    {
        idle_timer = timer_read();
        // Reset the seconds counter. Without this, something like press> leave x seconds> press, would be x seconds on the effective counter not 0 as it should.
        idle_second_counter = 0;
        if (!rgb_enabled_flag)
        {
            rgb_matrix_enable_noeeprom();
            rgb_matrix_set_flags(rgb_time_out_saved_flag);
            rgb_enabled_flag = true;
        }
    }

    switch (keycode)
    {

    case MD_BOOT:
        if (record->event.pressed)
        {
            key_timer = timer_read32();
        }
        else
        {
            if (timer_elapsed32(key_timer) >= 500)
            {
                reset_keyboard();
            }
        }
        return false;
    case RGB_TOG:
        if (record->event.pressed)
        {
            switch (rgb_matrix_get_flags())
            {
            case LED_FLAG_ALL:
            {
                rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR);
                rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
            case (LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER | LED_FLAG_INDICATOR):
            {
                rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
                rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
            case LED_FLAG_UNDERGLOW:
            {
                rgb_matrix_set_flags(LED_FLAG_NONE);
                rgb_matrix_disable_noeeprom();
            }
            break;
            default:
            {
                rgb_matrix_set_flags(LED_FLAG_ALL);
                rgb_matrix_enable_noeeprom();
            }
            break;
            }
        }
        return false;
    case WIN_PK:
        register_code(KC_LGUI);
        register_code(KC_TAB);
        unregister_code(KC_TAB);
        unregister_code(KC_LGUI);
        return false;
    case DBG_PRNT:
            if (record->event.pressed)
        {
        if (rgb_time_out_enable) {
            send_string(sendstring_commands[0]);
        } else {
            send_string(sendstring_commands[1]);
        }}
            return false;
    case ROUT_TG:
            if (record->event.pressed)
        {
                rgb_time_out_enable = !rgb_time_out_enable;
                rgb_time_out_user_value = rgb_time_out_enable;
        }
                return false;
    case LCAS_1 ... LCAS_9:
    {
        char cas[] = "1";
        cas[0] += (keycode - LCAS_1);

        register_code(KC_LSHIFT);
        register_code(KC_LCTRL);
        register_code(KC_LALT);
        send_string(cas);
        unregister_code(KC_LALT);
        unregister_code(KC_LCTRL);
        unregister_code(KC_LSHIFT);
    }

        return false;

        case WCS_H:
        register_code(KC_LSHIFT);
        register_code(KC_LCTRL);
        register_code(KC_LEFT_GUI);
        register_code(KC_H);
        unregister_code(KC_H);
        unregister_code(KC_LEFT_GUI);
        unregister_code(KC_LCTRL);
        unregister_code(KC_LSHIFT);
        return false;
    default:
        return true; // Process all other keycodes normally
    }
}

void matrix_init_user(void)
{
    // Enable or disable debugging
    debug_enable = false;
    debug_matrix = false;
    debug_keyboard = false;
    debug_mouse = false;

    idle_second_counter = 0;                          // Counter for number of seconds keyboard has been idle.
    key_event_counter = 0;                            // Counter to determine if keys are being held, neutral at 0.
    rgb_time_out_seconds = RGB_DEFAULT_TIME_OUT;      // RGB timeout initialized to its default configure in keymap.h
    rgb_time_out_enable = true;                       // Disable RGB timeout by default. Enable using toggle key.
    rgb_time_out_user_value = false;                  // Has to have the same initial value as rgb_time_out_enable.
    rgb_enabled_flag = true;                          // Initially, keyboard RGB is enabled. Change to false config.h initializes RGB disabled.
    rgb_time_out_fast_mode_enabled = false;           // RGB timeout fast mode disabled initially.
    rgb_time_out_saved_flag = rgb_matrix_get_flags(); // Save RGB matrix state for when keyboard comes back from ide.
};

void keyboard_post_init_user(void)
{
    rgb_matrix_enable();
}



void set_layer_color(int layer) {
    // if (layer == 0) { return; }
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        HSV hsv = {
            .h = pgm_read_byte(&ledmap[layer][i][0]),
            .s = pgm_read_byte(&ledmap[layer][i][1]),
            .v = pgm_read_byte(&ledmap[layer][i][2]),
        };
        if (hsv.h || hsv.s || hsv.v) {
            RGB rgb = hsv_to_rgb(hsv);
            float f = (float)rgb_matrix_config.hsv.v / UINT8_MAX;
            rgb_matrix_set_color(i, f * rgb.r, f * rgb.g, f * rgb.b);
        }
        //  else if (layer != 1) {
        //     // Only deactivate non-defined key LEDs at layers other than FN. Because at FN we have RGB adjustments and need to see them live.
        //     // If the values are all false then it's a transparent key and deactivate LED at this layer
        //     rgb_matrix_set_color(i, 0, 0, 0);
        // }
    }
}

void matrix_scan_user(void)
{
    if (rgb_time_out_enable && rgb_enabled_flag)
    {
        // If the key event counter is not zero then some key was pressed down but not released, thus reset the timeout counter.
        if (key_event_counter)
        {
            idle_second_counter = 0;
        }
        else if (timer_elapsed(idle_timer) > MILLISECONDS_IN_SECOND)
        {
            idle_second_counter++;
            idle_timer = timer_read();
        }

        if (idle_second_counter >= rgb_time_out_seconds)
        {
            rgb_time_out_saved_flag = rgb_matrix_get_flags();
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            rgb_enabled_flag = false;
            idle_second_counter = 0;
        }
    }
}

void rgb_matrix_indicators_user(void) {
    if (disable_layer_color ||
        rgb_matrix_get_flags() == LED_FLAG_NONE ||
        rgb_matrix_get_flags() == LED_FLAG_UNDERGLOW) {
            return;
        }
    set_layer_color(get_highest_layer(layer_state));
}
