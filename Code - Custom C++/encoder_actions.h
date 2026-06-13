#ifndef ENCODER_ACTIONS_H
#define ENCODER_ACTIONS_H

#pragma once

class encoder_actions
{
public:
    encoder_actions();
    ~encoder_actions();
    static void handle_turn(uint8_t id, uint8_t rotation, uint8_t layer);
    static void thud_start(uint16_t keycode);
    static void thud_scan();

    static void vol_up();
    static void vol_down();
    static void next_track();
    static void prev_track();
    static void ui_up();
    static void ui_down();
    static int16_t enc3_physical_delta;
    static bool enc3_physical_button_pressed;

private:
    static bool thud_que;
    static uint32_t ellapsed_thud;
    static uint32_t current_thud;
    static uint16_t empty_report;

};

#endif