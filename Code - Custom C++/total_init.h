#ifndef TOTAL_INIT_H
#define TOTAL_INIT_H

#pragma once

#include <atomic>
#include "pico/util/queue.h"
#include "ws2812.h"

class total_init
{
public:
    total_init();
    ~total_init();
    static void total_init_core0();
    static void total_init_core1();
    static void layer_change(uint8_t layer);
    static uint8_t get_layer();
    static void set_song(const char* song);
    static bool move_queue(const char * incoming_title);
    static void update_song_display_check(void);
    static const char* get_song();
    static char* volatile_to_const(volatile char* input);
    static void try_and_fail(volatile char * incoming_title);
    static void try_again(const char * song);
    static void check_failure();
    static uint8_t brightness_led(uint8_t value);
    static void set_brightness_percent(uint8_t percent);
    static void increment_brightness(void);
    static void decrement_brightness(void);
    static void check_layer();
    static uint8_t get_brightness(void);
    static void load_led_method(void);
    static void increment_led_method(void);
    static void decrement_led_method(void);
    static uint8_t get_led_pattern(void);
    static void set_pattern(uint8_t pattern);
private:
    static uint32_t frame_count;
    static volatile uint8_t current_layer;
    static volatile char current_song[128];
    static bool failure;
    static char failed[128];
    static uint32_t fail_time;
    static std::atomic<uint8_t> brightness_percent;
    static queue_t song_queue;
    static char end_queue[128];
    static volatile bool layer_changed;
    static led_control::Ws2812Strip led_strip;
    static std::atomic<uint8_t> led_method;
};

#endif
