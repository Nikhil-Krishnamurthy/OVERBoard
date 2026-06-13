#include "pico/stdlib.h"
#include "lvgl-master/lvgl.h"
#include "i2c_control.h"
#include "spi_control.h"
#include "uart_control.h"
#include "ili9341.h"
#include <array>
#include <string>
#include <iostream>
#include "pico/util/queue.h"
#include "lvgl_helper.h"
#include "pico/mutex.h"
#include <string.h>
#include <atomic>
#include "ws2812.h"
#include "total_init.h"

#define MAX_SONG_LENGTH 128

std::atomic<uint8_t> total_init::brightness_percent{100};

volatile bool total_init::layer_changed = false;
volatile uint8_t total_init::current_layer = 0;
volatile char total_init::current_song[MAX_SONG_LENGTH];
char total_init::failed[MAX_SONG_LENGTH];
bool total_init::failure = false;
uint32_t total_init::fail_time = 0;
typedef struct {
    char title[MAX_SONG_LENGTH];
} song_packet_t;
uint32_t total_init::frame_count = 0;
std::atomic<uint8_t> total_init::led_method{0};

char total_init::end_queue[MAX_SONG_LENGTH] = "No song playing";
queue_t total_init::song_queue;

mutex_t layer_mutex;
mutex_t lvgl_mutex;

led_control::Ws2812Strip total_init::led_strip;

using led_method_ptr = void (led_control::Ws2812Strip::*)(uint32_t);

// 2. Populate the array with the actual addresses of the class methods
constexpr led_method_ptr LED_METHODS[] = {
    &led_control::Ws2812Strip::pattern_snakes,
    &led_control::Ws2812Strip::pattern_random,
    &led_control::Ws2812Strip::pattern_sparkle,
    &led_control::Ws2812Strip::pattern_greys
};

total_init::total_init()
{
    
}

total_init::~total_init()
{

}
//core 0 only
void total_init::total_init_core0(){
    mutex_init(&layer_mutex);
    mutex_init(&lvgl_mutex);
    queue_init(&song_queue, sizeof(song_packet_t), 4);
    i2c_control::i2c_init_custom();
    uart_control::uart_init_custom();
    led_strip.init();
}

//core 1 only
void total_init::total_init_core1(){
    //spi_control::spi_init_custom();
    LCD_setPins(21, 17, -1, 18, 19);
    LCD_setSPIperiph(spi0);
    LCD_initDisplay();
    LCD_setRotation(0);

}

//both core - mutex blocking/protection - uses temp variable to store to output later
void total_init::layer_change(uint8_t layer){
    mutex_enter_blocking(&layer_mutex);
    current_layer = layer;
    layer_changed = true;
    mutex_exit(&layer_mutex);
}

void total_init::check_layer(){
    bool intro = false;
    uint8_t temp_layer;
    mutex_enter_blocking(&layer_mutex);
    if(layer_changed){
        layer_changed = false;
        intro = true;
        temp_layer = current_layer;
    }
    mutex_exit(&layer_mutex);

    if(intro){
        uart_control::broadcast_layer(temp_layer);
    }
}

//both core - mutex blocking/protection
uint8_t total_init::get_layer(){
    mutex_enter_blocking(&layer_mutex);
    uint8_t return_statement = current_layer;
    mutex_exit(&layer_mutex);
    return return_statement;
}

//core 0 only
void total_init::set_song(const char* song){
    strncpy((char*)current_song, song, 127);
    current_song[127] = '\0';

    if(!move_queue((const char*)current_song)){
        strncpy(failed, (const char*)current_song, 127);
        failed[127] = '\0';
        failure = true;
        fail_time = to_ms_since_boot(get_absolute_time());
    }
}

//core 0 only
bool total_init::move_queue(const char * incoming_title){
    if(incoming_title == NULL) return false;
    song_packet_t packet;
    strncpy(packet.title, incoming_title, sizeof(packet.title) - 1);
    packet.title[sizeof(packet.title) - 1] = '\0';

    // Push into the queue without blocking. If the queue is full, it skips.
    return queue_try_add(&song_queue, &packet);
}

//core 1 only
void total_init::update_song_display_check(void) {
    
    song_packet_t received_packet;

    // If there is a packet waiting in the pipe, pull it out
    if (queue_try_remove(&song_queue, &received_packet)) {
        strncpy(end_queue, received_packet.title, sizeof(end_queue) - 1);
        end_queue[sizeof(end_queue) - 1] = '\0';
    }
}
//core 1 only
const char * total_init::get_song() {
    return end_queue;
}

//core 0 only
void total_init::try_again(const char* song){
    if(move_queue(song)){
        failure = false;
    } else {
        strncpy(failed, song, 127);
        failed[127] = '\0';
        fail_time = to_ms_since_boot(get_absolute_time());
    }
}

//core 0 only
void total_init::check_failure(){
    uint32_t current_time = to_ms_since_boot(get_absolute_time());
    if(failure && (current_time - fail_time >= 50)){
        try_again(failed);
    }
}

uint8_t total_init::brightness_led(uint8_t value){
    uint8_t temp_brightness = value * brightness_percent / 100;
    return temp_brightness;
}

void total_init::set_brightness_percent(uint8_t percent){
    brightness_percent = percent;
}

void total_init::increment_brightness(void){
    if(brightness_percent < 100){
        brightness_percent++;
    }
}

void total_init::decrement_brightness(void){
    if(brightness_percent > 0){
        brightness_percent--;
    }
}

uint8_t total_init::get_brightness(void){
    return brightness_percent;
}

void total_init::load_led_method(){
    (led_strip.*LED_METHODS[led_method])(frame_count);
    frame_count++;
}

void total_init::increment_led_method(){
    if(led_method < 3){
        led_method++;
    }
}
void total_init::decrement_led_method(){
    if(led_method > 0){
        led_method--;
    }
}

uint8_t total_init::get_led_pattern(void){
    // Implementation for getting the current LED pattern
    return led_method;
}