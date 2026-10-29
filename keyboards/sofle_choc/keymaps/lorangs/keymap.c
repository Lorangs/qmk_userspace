// Copyright 2026 Lorang
// SPDX-License-Identifier: GPL-2.0-or-later

/* Sofle Choc - Norwegian QWERTY, 4 layers
 *
 * IMPORTANT: set the OS keyboard layout to Norwegian. QMK only sends key
 * positions; the NO_* keycodes below are named after what a Norwegian host
 * layout prints for that position.
 *
 * Layers:
 *   0 _BASE   Norwegian QWERTY
 *   1 _NUM    Numpad (right hand) + every Norwegian symbol
 *   2 _NAV    Arrows (HJKL), Home/End/PgUp/PgDn, mouse, mods, clipboard, F1-F12
 *   3 _MEDIA  Media, screen brightness, RGB, bootloader  (hold LOWR + UPPR)
 *
 * Dead keys on a Norwegian host: ¨ ^ ~ ` ´ wait for the next key.
 * Press them and then Space to get the bare character.
 */
#include QMK_KEYBOARD_H
#include "keymap_norwegian.h"

// QMK's NO_EURO is AltGr+5, which is € on Windows but ½ on Linux (xkb "no").
// AltGr+E gives € on both.
#define NO_EUR ALGR(NO_E)

enum layers {
    _BASE,
    _NUM,
    _NAV,
    _MEDIA,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* 0: BASE - Norwegian QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  |   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  +   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  Å   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ø  |  Æ   |
 * |------+------+------+------+------+------| Mute  |    | Pause |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   -  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LCtl | LGUI | LAlt | LOWR | /Space  /       \Enter \  | UPPR | Bspc |AltGr | RCtl |
 *            `----------------------------------'           '------''---------------------------'
 *  Left encoder: volume       Right encoder: scroll up/down
 */
[_BASE] = LAYOUT(
    NO_PIPE, NO_1,    NO_2,    NO_3,    NO_4,    NO_5,                         NO_6,    NO_7,    NO_8,    NO_9,    NO_0,    NO_PLUS,
    KC_TAB,  NO_Q,    NO_W,    NO_E,    NO_R,    NO_T,                         NO_Y,    NO_U,    NO_I,    NO_O,    NO_P,    NO_ARNG,
    KC_ESC,  NO_A,    NO_S,    NO_D,    NO_F,    NO_G,                         NO_H,    NO_J,    NO_K,    NO_L,    NO_OSTR, NO_AE,
    KC_LSFT, NO_Z,    NO_X,    NO_C,    NO_V,    NO_B,    KC_MUTE,    KC_MPLY, NO_N,    NO_M,    NO_COMM, NO_DOT,  NO_MINS, KC_RSFT,
                      KC_LCTL, KC_LGUI, KC_LALT, TL_LOWR, KC_SPC,     KC_ENT,  TL_UPPR, KC_BSPC, KC_RALT, KC_RCTL
),

/* 1: NUM - numpad on the right, every Norwegian symbol around it
 * Top row = Shift+number on a Norwegian keyboard (each symbol sits above "its" digit).
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  §   |  !   |  "   |  #   |  ¤   |  %   |                    |  &   |  /   |  (   |  )   |  =   |  ?   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  ¨   |  @   |  {   |  }   |  $   |  ~   |                    |   7  |   8  |   9  |   *  |   ;  |  :   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  ´   |  \   |  |   |  €   |  '   |  ^   |-------.    ,-------|   4  |   5  |   6  |   0  |   -  |  +   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |  £   |  <   |  >   |  [   |  ]   |  `   |-------|    |-------|   1  |   2  |   3  |   .  |   ,  |  _   |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |[held]| /       /       \Enter \ |      | Del  |     |  µ   |
 *            `----------------------------------'           '------''---------------------------'
 *  No Shift on this layer: every symbol has its own key.
 *  Left encoder: zoom out/in (Ctrl -/+)    Right encoder: scroll (inherited)
 */
[_NUM] = LAYOUT(
    NO_SECT, NO_EXLM, NO_DQUO, NO_HASH, NO_CURR, NO_PERC,                      NO_AMPR, NO_SLSH, NO_LPRN, NO_RPRN, NO_EQL,  NO_QUES,
    NO_DIAE, NO_AT,   NO_LCBR, NO_RCBR, NO_DLR,  NO_TILD,                      NO_7,    NO_8,    NO_9,    NO_ASTR, NO_SCLN, NO_COLN,
    NO_ACUT, NO_BSLS, NO_PIPE, NO_EUR,  NO_QUOT, NO_CIRC,                      NO_4,    NO_5,    NO_6,    NO_0,    NO_MINS, NO_PLUS,
    NO_PND,  NO_LABK, NO_RABK, NO_LBRC, NO_RBRC, NO_GRV,  _______,    _______, NO_1,    NO_2,    NO_3,    NO_DOT,  NO_COMM, NO_UNDS,
                      _______, _______, _______, _______, _______,    KC_ENT, _______, KC_DEL, _______,  NO_MICR
),

/* 2: NAV - movement + F-keys
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |MsBtn1|MsBtn3|MsBtn2|      |                    | Home | PgDn | PgUp | End  | Ins  | Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | GUI  | Alt  | Ctrl |Shift |      |-------.    ,-------| Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy |Paste |      |-------|    |-------|MsLeft|MsDown| MsUp |MsRght|      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |[held]|      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 *  Left encoder: horizontal scroll    Right encoder: Page Up / Page Down
 */
[_NAV] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    _______, XXXXXXX, MS_BTN1, MS_BTN3, MS_BTN2, XXXXXXX,                      KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_INS,  KC_DEL,
    _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX,                      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX, XXXXXXX,
    _______, C(NO_Z), C(NO_X), C(NO_C), C(NO_V), XXXXXXX, _______,    _______, MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XXXXXXX, _______,
                      _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______
),

/* 3: MEDIA - hold LOWR + UPPR
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | BOOT |EEClr |      |      |      |      |                    |      |      |      |      |EEClr | BOOT |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |RGBTog|RGBMod|Hue+  | Sat+ | Bri+ |                    | Stop |ScrBr-|ScrBr+|      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps |      |RGBRMd|Hue-  | Sat- | Bri- |-------.    ,-------| Prev | Vol- | Vol+ | Next | Play | Mute |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |Speed-|Speed+|-------|    |-------|WwwBck|WwwFwd|WwwRef| Calc |PrtScr|      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |[held]| /       /       \      \  |[held]|      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 *  Left encoder: previous/next track    Right encoder: screen brightness
 */
[_MEDIA] = LAYOUT(
    QK_BOOT, EE_CLR,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,  QK_BOOT,
    XXXXXXX, RM_TOGG, RM_NEXT, RM_HUEU, RM_SATU, RM_VALU,                      KC_MSTP, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_CAPS, XXXXXXX, RM_PREV, RM_HUED, RM_SATD, RM_VALD,                      KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY, KC_MUTE,
    _______, XXXXXXX, XXXXXXX, XXXXXXX, RM_SPDD, RM_SPDU, _______,    _______, KC_WBAK, KC_WFWD, KC_WREF, KC_CALC, KC_PSCR, XXXXXXX,
                      _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______
),
};

#if defined(ENCODER_MAP_ENABLE)
// Encoder 0 = left half, encoder 1 = right half.
// If a direction feels backwards, swap the two keycodes in that pair.
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]  = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD),           ENCODER_CCW_CW(MS_WHLU, MS_WHLD) },
    [_NUM]   = { ENCODER_CCW_CW(KC_BRID, KC_BRIU),           ENCODER_CCW_CW(MS_WHLL, MS_WHLR) },
    [_NAV]   = { ENCODER_CCW_CW(C(NO_MINS), C(NO_PLUS)),     ENCODER_CCW_CW(KC_PGDN, KC_PGUP) },
    [_MEDIA] = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT),           ENCODER_CCW_CW(_______, _______) },
};
#endif

#ifdef OLED_ENABLE
    #include "sol.h"
// Master half shows the active layer; slave keeps the stock QMK logo.
bool oled_task_user(void) {
    if (!is_keyboard_master()) {
        oled_write_raw_P(oled_image, sizeof (oled_image));
        return false;
    }
    oled_write_ln_P(PSTR("Sofle Choc  [NO]"), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:  oled_write_ln_P(PSTR("Base"), false);        break;
        case _NUM:   oled_write_ln_P(PSTR("Num / Sym"), false);   break;
        case _NAV:   oled_write_ln_P(PSTR("Nav / Mouse"), false); break;
        case _MEDIA: oled_write_ln_P(PSTR("Media / RGB"), false); break;
    }
    oled_write_ln_P(host_keyboard_led_state().caps_lock ? PSTR("CAPS") : PSTR(""), false);
    return false;
}
#endif

#ifdef RGB_MATRIX_ENABLE
// While a non-base layer is held, light only the keys that do something on
// that layer, in a per-layer colour. Uses the current RGB brightness setting.
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    uint8_t layer = get_highest_layer(layer_state);
    if (layer == _BASE) {
        return false;
    }
    static const uint8_t PROGMEM layer_hue[] = {
        [_NUM]   = 85,  // green
        [_NAV]   = 170, // blue
        [_MEDIA] = 213, // magenta
    };
    hsv_t hsv = {pgm_read_byte(&layer_hue[layer]), 255, rgb_matrix_get_val()};
    rgb_t rgb = hsv_to_rgb(hsv);

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];
            if (index == NO_LED || index < led_min || index >= led_max) {
                continue;
            }
            if (keymap_key_to_keycode(layer, (keypos_t){.col = col, .row = row}) > KC_TRNS) {
                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
            } else {
                rgb_matrix_set_color(index, 0, 0, 0);
            }
        }
    }
    return false;
}
#endif
