#ifndef LVGL_HELPER_H
#define LVGL_HELPER_H

#pragma once

#include "lvgl-master/lvgl.h"
#include <string>
#include <string.h>

class lvgl_helper
{
public:
    lvgl_helper();
    ~lvgl_helper();
    static void song_and_layer(lv_obj_t * label, uint8_t screen_index);
    static void main_menu(lv_obj_t * label);
    static void led_menu(lv_obj_t * label);
    static void init_all_ui_views();
    static void btn_event_cb(lv_event_t * e);
    static void check_layer_update();
    static void brightness_display(lv_obj_t * parent);
    static void pattern_display(lv_obj_t * parent);
    static void sound_board_menu(lv_obj_t * label);
    static void create_sidebar(lv_obj_t * parent);
    static void encoder_read_cb(lv_indev_t * indev, lv_indev_data_t * data);
private:
    static bool song;
    static lv_obj_t * layer0_screen;
    static lv_obj_t * layer1_screen;
    static lv_obj_t * layer2_screen;
    static lv_obj_t * layer3_screen;
    static uint32_t MY_EVENT_LAYER_CHANGED;
    static uint8_t previous;
    static uint8_t layers[4];
    static lv_obj_t * song_label;
    static lv_obj_t * led_brightness_label;
    static lv_obj_t * led_pattern_label;
    static uint8_t last_brightness;
    static uint8_t last_led_pattern;
    static std::string led_patterns[];
    static lv_obj_t * song_labels[2];
    // Add these to your static instantiations at the top of your .cpp file
    static lv_group_t * navigation_group;
    static lv_indev_t * encoder_indev;
};

#endif