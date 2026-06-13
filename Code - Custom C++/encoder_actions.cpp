#include <cstdint>
#include "total_init.h"
#include "pico/stdlib.h"
#include "encoder_actions.h"
#include "tusb.h"

#define TOTAL_LAYERS 4
#define NUM_ENCODERS 3
#define TOTAL_ROTATIONS 2

bool encoder_actions::thud_que = 0;
uint32_t encoder_actions::ellapsed_thud = 0;
uint32_t encoder_actions::current_thud = 0;
uint16_t encoder_actions::empty_report = 0;
int16_t encoder_actions::enc3_physical_delta = 0;
bool encoder_actions::enc3_physical_button_pressed = false;

using encoder_array = void(*)(void);

constexpr encoder_array ENCODER_COMMAND_MATRIX[TOTAL_LAYERS][NUM_ENCODERS][TOTAL_ROTATIONS]{
    {
        {&encoder_actions::vol_up, &encoder_actions::vol_down}, //encoder 1 layer 1
        {&encoder_actions::next_track, &encoder_actions::prev_track},//encoder 2 layer 1
        {&encoder_actions::ui_up, &encoder_actions::ui_down}//encoder 3 layer 1
    },
    {
        //macro layer - no changes
        {&encoder_actions::vol_up, &encoder_actions::vol_down}, //encoder 1 layer 1
        {&encoder_actions::next_track, &encoder_actions::prev_track},//encoder 2 layer 1
        {&encoder_actions::ui_up, &encoder_actions::ui_down}//encoder 3 layer 1
    },
    {
        //led layer - brightness + lighting patterns
        {&total_init::increment_brightness, &total_init::decrement_brightness},
        {&total_init::increment_led_method, &total_init::decrement_led_method},
        {&encoder_actions::ui_up, &encoder_actions::ui_down}
    },
    {
        //sound board layer - dont know what to put here yet
        {&encoder_actions::vol_up, &encoder_actions::vol_down}, //encoder 1 layer 1
        {&encoder_actions::next_track, &encoder_actions::prev_track},//encoder 2 layer 1
        {&encoder_actions::ui_up, &encoder_actions::ui_down}//encoder 3 layer 1
    }
};

encoder_actions::encoder_actions()
{

}

encoder_actions::~encoder_actions()
{

}

void encoder_actions::handle_turn(uint8_t id, uint8_t rotation, uint8_t layer){
    ENCODER_COMMAND_MATRIX[layer][id][rotation]();
}

void encoder_actions::thud_start(uint16_t keycode){
    if(tud_hid_ready()){
        tud_hid_report(2, &keycode, sizeof(keycode));
        thud_que = true;
        ellapsed_thud = to_ms_since_boot(get_absolute_time());
    }
}

void encoder_actions::thud_scan(){
    if(thud_que != 0){
        current_thud = to_ms_since_boot(get_absolute_time());
        if(tud_hid_ready()){
            if(current_thud - ellapsed_thud >= 10){
                tud_hid_report(2, &empty_report, sizeof(empty_report));
                thud_que = false;
            }
        }
    }
}



void encoder_actions::vol_up(){
    thud_start(HID_USAGE_CONSUMER_VOLUME_INCREMENT);
}

void encoder_actions::vol_down(){
    thud_start(HID_USAGE_CONSUMER_VOLUME_DECREMENT);
}

void encoder_actions::next_track(){
    thud_start(HID_USAGE_CONSUMER_SCAN_NEXT);
}

void encoder_actions::prev_track(){
    thud_start(HID_USAGE_CONSUMER_SCAN_PREVIOUS);
}

void encoder_actions::ui_up(){
    enc3_physical_delta++;
}

void encoder_actions::ui_down(){
    enc3_physical_delta--;
}