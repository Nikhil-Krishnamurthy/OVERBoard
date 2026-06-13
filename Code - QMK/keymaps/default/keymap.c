// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include <uart.h>

enum keycodes{
    shiftLayerUp,
    shiftLayerDown,
    enterScreen,
    backScreen,
    shiftLayerDefault,
    brightness_default,
    pattern_default,
};

#define LAYER_START 0
#define LAYER_END 2
#define DEFAULT_LAYER 0

uint8_t currentLayer = 0;
uint8_t next_command = -1;

void keyboard_post_init_user(void){
    uart_init(115200);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case shiftLayerUp:
            if (record->event.pressed) {
                if(currentLayer >= LAYER_END){
                    currentLayer = 0;
                }
                else{
                    currentLayer = currentLayer + 1;
                }
                layer_move(currentLayer);
                uart_write(0x80 | currentLayer);
            }
            return false;
            
        case shiftLayerDown:
            if (record->event.pressed) {
                if(currentLayer <= LAYER_START){
                    currentLayer = LAYER_END;
                }
                else{
                    currentLayer = currentLayer - 1;
                }
                layer_move(currentLayer);
                uart_write(0x80 | currentLayer);
            }
            return false;
        
        case enterScreen:
            if(record->event.pressed) {
                uart_write(0x79);
            }
            else {
                uart_write(0x7A);
            }
            return false;
            
        case backScreen:
            if(record->event.pressed) {
                uart_write(0x78);
            }
            else {
                uart_write(0x7A);
            }
            return false;

        case brightness_default:
            if(record->event.pressed) {
                uart_write(0x7B);
            }
            return false;
        case pattern_default:
            if(record->event.pressed) {
                uart_write(0x7C);
            }
            return false;
        default:
            return true;
        }
    }
void housekeeping_task_user(){
    if(uart_available()){
        uint8_t next_command = uart_read();
        if(next_command & 0x80){
            uint8_t layer_select = next_command & 0x7F;
            layer_move(layer_select);
        }
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐   ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┐
     * │Esc│   │F1 │F2 │F3 │F4 │ │F5 │F6 │F7 │F8 │ │F9 │F10│F11│F12│   | EC11(1) |
     * └───┘   └───┴───┴───┴───┘ └───┴───┴───┴───┘ └───┴───┴───┴───┘ 
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┐ 
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp│ 
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤ 
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │ 
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤ 
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter │   | EC11(2) |
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤     ┌───┐
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │    Shift │     │ ↑ │      | EC11(3) | 
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬────┤ ┌───┼───┼───┐
     * │Ctrl│GUI │Alt │                        │ Alt│ GUI│Menu│Ctrl│ │ ← │ ↓ │ → │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘ └───┴───┴───┘
     */
    
    //default
     [0] = LAYOUT_tkl_ansi(
        KC_ESC,           KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,     KC_MUTE,

        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,    
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,    
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,              KC_MPLY,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP, enterScreen,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT
    ),
    //Macros
    [1] =  LAYOUT_tkl_ansi(
        KC_ESC,           KC_F13,  KC_F14,  KC_F15,   KC_F16,   KC_F17,   KC_F18, KC_F19, KC_F20, KC_F21,  KC_F22,  KC_F23, KC_F24,      KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [2] = LAYOUT_tkl_ansi(
        KC_ESC,           KC_F1,  KC_F2,  KC_F3,   KC_F4,   KC_F5,   KC_F6, KC_F7, KC_F8, KC_F9,  KC_F10,  KC_F11, KC_F12,      brightness_default,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, pattern_default,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [3] = LAYOUT_tkl_ansi(
        KC_ESC,           HYPR(KC_F13),   HYPR(KC_F14),   HYPR(KC_F15),   HYPR(KC_F16),   HYPR(KC_F17),   HYPR(KC_F18),   HYPR(KC_F19),   HYPR(KC_F20),   HYPR(KC_F21),   HYPR(KC_F22),  HYPR(KC_F23),  HYPR(KC_F24),     KC_MUTE,

        KC_GRV,  HYPR(KC_1),    HYPR(KC_2),    HYPR(KC_3),    HYPR(KC_4),    HYPR(KC_5),    HYPR(KC_6),    HYPR(KC_7),    HYPR(KC_8),    HYPR(KC_9),    HYPR(KC_0),    HYPR(KC_MINS), HYPR(KC_EQL),  KC_BSPC,    
        KC_TAB,  MEH(KC_Q),    MEH(KC_W),    HYPR(KC_E),    HYPR(KC_R),    MEH(KC_T),    MEH(KC_Y),    HYPR(KC_U),    HYPR(KC_I),    MEH(KC_O),    MEH(KC_P),    HYPR(KC_LBRC), HYPR(KC_RBRC), HYPR(KC_BSLS),    
        KC_CAPS, MEH(KC_A),    HYPR(KC_S),    MEH(KC_D),    HYPR(KC_F),    HYPR(KC_G),    HYPR(KC_H),    HYPR(KC_J),    HYPR(KC_K),    MEH(KC_L),    HYPR(KC_SCLN), HYPR(KC_QUOT),          KC_ENT,              KC_MPLY,
        KC_LSFT,          HYPR(KC_Z),   MEH(KC_X),    HYPR(KC_C),    HYPR(KC_V),    MEH(KC_B),    MEH(KC_N),    HYPR(KC_M),    HYPR(KC_COMM), HYPR(KC_DOT),  HYPR(KC_SLSH),          KC_RSFT,             KC_UP, enterScreen,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT
    )
};
