#include QMK_KEYBOARD_H

enum planck_layers {
  _QWERTY,
  _COLEMAK,
  _LOWER,
  _RAISE,
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_planck_grid(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_MINS, KC_EQL,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_BSLS, KC_QUOT, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
    KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_BSPC, KC_DEL,  KC_ENT,  KC_SPC,  LOWER,   RAISE,   KC_TAB,  KC_ESC
  ),

  [_COLEMAK] = LAYOUT_planck_grid(
    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_MINS, KC_EQL,  KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,
    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_BSLS, KC_QUOT, KC_H,    KC_N,    KC_E,    KC_I,    KC_O,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RBRC, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
    KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_BSPC, KC_DEL,  KC_ENT,  KC_SPC,  LOWER,   RAISE,   KC_TAB,  KC_ESC
  ),

  [_LOWER] = LAYOUT_planck_grid(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_GRV,  XXXXXXX, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_LPRN, KC_RPRN, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, KC_ESC,  XXXXXXX, XXXXXXX, KC_TAB,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),

  [_RAISE] = LAYOUT_planck_grid(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  XXXXXXX,
    QWERTY,  COLEMAK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MPLY, KC_MUTE, KC_VOLD, KC_VOLU,
    KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
  ),
};

#ifdef AUDIO_ENABLE
  float qwerty_song[][2] = SONG(QWERTY_SOUND);
  float colemak_song[][2] = SONG(COLEMAK_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(qwerty_song);
        #endif
      }
      return false;
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
        #ifdef AUDIO_ENABLE
          stop_all_notes();
          PLAY_SONG(colemak_song);
        #endif
      }
      return false;
  }
  return true;
}
