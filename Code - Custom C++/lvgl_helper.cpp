#include "lvgl-master/lvgl.h"
#include "total_init.h"
#include "encoder_actions.h"
#include <string.h>
#include <stdio.h>
#include <string>
#include "pico/mutex.h"
#include "lvgl_helper.h"

bool lvgl_helper::song = true;
lv_obj_t * lvgl_helper::song_label = NULL;
lv_obj_t * lvgl_helper::layer0_screen = NULL;
lv_obj_t * lvgl_helper::layer1_screen = NULL;
lv_obj_t * lvgl_helper::layer2_screen = NULL;
lv_obj_t * lvgl_helper::layer3_screen = NULL;
lv_obj_t * lvgl_helper::led_brightness_label = NULL;
lv_obj_t * lvgl_helper::led_pattern_label = NULL;
uint8_t lvgl_helper::layers[4] = {0, 1, 2, 3};
uint32_t lvgl_helper::MY_EVENT_LAYER_CHANGED;
uint8_t lvgl_helper::previous = 0;
uint8_t lvgl_helper::last_brightness = 100;
uint8_t lvgl_helper::last_led_pattern = 0;
lv_obj_t * lvgl_helper::song_labels[2] = {NULL, NULL};
std::string lvgl_helper::led_patterns[] = {"Snakes", "Random", "Sparkles", "Grey"};
// Add these to your static instantiations at the top of your .cpp file
lv_group_t * lvgl_helper::navigation_group = NULL;
lv_indev_t * lvgl_helper::encoder_indev = NULL;
extern mutex_t lvgl_mutex; // Created in main setup, used here


lvgl_helper::lvgl_helper()
{

}

lvgl_helper::~lvgl_helper()
{

}

void lvgl_helper::create_sidebar(lv_obj_t * parent) {
    const char* btn_labels[] = {"Main", "Macro", "LED", "Sound Board"};
    lv_obj_t* target_screens[] = {layer0_screen, layer1_screen, layer2_screen, layer3_screen};

    for (int i = 0; i < 4; i++) {
        lv_obj_t * btn = lv_button_create(parent);
        lv_obj_set_pos(btn, 10, 10 + (i * 60)); // Math-driven Y layout spacing
        lv_obj_set_size(btn, 120, 50);
        lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, &layers[i]);

        lv_obj_t * btn_lbl = lv_label_create(btn);
        lv_label_set_text(btn_lbl, btn_labels[i]);
        lv_obj_center(btn_lbl);

        // Visual Context Highlighter
        if (parent == target_screens[i]) {
            lv_obj_set_style_bg_color(btn, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
        } else {
            lv_obj_set_style_bg_color(btn, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN);
        }

        // Essential Encoder Hooks: Registers this item to be selected by the physical wheel
        if (navigation_group != NULL) {
            lv_group_add_obj(navigation_group, btn);
        }
    }
}

void lvgl_helper::song_and_layer(lv_obj_t * parent, uint8_t screen_index) {
    lv_obj_t * s_label = lv_label_create(parent);
    
    lv_label_set_text(s_label, total_init::get_song()); 
    lv_obj_set_style_text_color(s_label, lv_color_hex(0x00FFCC), LV_PART_MAIN); 
    lv_obj_set_pos(s_label, 150, 200); 
    lv_label_set_long_mode(s_label, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_set_width(s_label, 240); 

    // Safely store the pointer into the array if it falls within valid index bounds
    if (screen_index < 2) {
        song_labels[screen_index] = s_label;
    }
}

void lvgl_helper::main_menu(lv_obj_t * label){
    lv_obj_set_style_bg_color(label, lv_color_hex(0x201a36), LV_PART_MAIN);

    create_sidebar(label);

    lv_obj_t * label1 = lv_label_create(label);
    lv_label_set_text(label1, "Encoder 1: VOLUME DOWN, MUTE, VOLUME UP");
    lv_obj_set_style_text_color(label1, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_pos(label1, 150, 10);

    lv_obj_t * label2 = lv_label_create(label);
    lv_label_set_text(label2, "Encoder 2: Previous Song, Pause & Play, Next Song");
    lv_obj_set_style_text_color(label2, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_pos(label2, 150, 50);

    lv_obj_t * label3 = lv_label_create(label);
    lv_label_set_text(label3, "Encoder 3: Down, Select, Up");
    lv_obj_set_style_text_color(label3, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_pos(label3, 150, 90);

    if(label == layer0_screen){
        song_and_layer(label, 0);
    }
    if(label == layer1_screen){
        song_and_layer(label, 1);
    }
}
void lvgl_helper::led_menu(lv_obj_t * label){
    lv_obj_set_style_bg_color(label, lv_color_hex(0x201a36), LV_PART_MAIN);

    create_sidebar(label);

    lv_obj_t * label1 = lv_label_create(label);
    lv_label_set_text(label1, "Encoder 1: Brightness Down, Default Brightness, Brightness Up");
    lv_obj_set_style_text_color(label1, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_pos(label1, 150, 10);

    lv_obj_t * label2 = lv_label_create(label);
    lv_label_set_text(label2, "Encoder 2: Previous Pattern, Default Pattern, Next Pattern");
    lv_obj_set_style_text_color(label2, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_pos(label2, 150, 50);

    lv_obj_t * label3 = lv_label_create(label);
    lv_label_set_text(label3, "Encoder 3: Down, Select, Up");
    lv_obj_set_style_text_color(label3, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_pos(label3, 150, 90);

    brightness_display(label);
    pattern_display(label);
    
}

void lvgl_helper::sound_board_menu(lv_obj_t * label) {
    // Implementation for the sound board menu
    lv_obj_set_style_bg_color(label, lv_color_hex(0x201a36), LV_PART_MAIN);

    //Button 1 - switches to layer 1
    create_sidebar(label);

    lv_obj_t * label1 = lv_label_create(label);
    lv_label_set_text(label1, "Encoder 1: VOLUME DOWN, MUTE, VOLUME UP");
    lv_obj_set_style_text_color(label1, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_pos(label1, 150, 10);

    lv_obj_t * label2 = lv_label_create(label);
    lv_label_set_text(label2, "Encoder 2: Previous Song, Pause & Play, Next Song");
    lv_obj_set_style_text_color(label2, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_pos(label2, 150, 50);

    lv_obj_t * label3 = lv_label_create(label);
    lv_label_set_text(label3, "Encoder 3: Down, Select, Up");
    lv_obj_set_style_text_color(label3, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_pos(label3, 150, 90);

    lv_obj_t * label4 = lv_label_create(label);
    lv_label_set_text(label4, "Loaded Sounds: Teto");
    lv_obj_set_style_text_color(label4, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_pos(label4, 150, 130);
}

void lvgl_helper::encoder_read_cb(lv_indev_t * indev, lv_indev_data_t * data) {
    // Directly inject your low-level hardware tracking values here
    data->enc_diff = encoder_actions::enc3_physical_delta;
    encoder_actions::enc3_physical_delta = 0; // Clear accumulated steps after read tracking

    data->state = encoder_actions::enc3_physical_button_pressed ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
}

void lvgl_helper::init_all_ui_views() {
    navigation_group = lv_group_create();
    lv_group_set_default(navigation_group);

    encoder_indev = lv_indev_create();
    lv_indev_set_type(encoder_indev, LV_INDEV_TYPE_ENCODER);
    lv_indev_set_read_cb(encoder_indev, encoder_read_cb);
    lv_indev_set_group(encoder_indev, navigation_group);
    
    // --- 1. BUILD THE MAIN MENU VIEW ---
    layer0_screen = lv_obj_create(NULL); // Passing NULL creates a clean base screen
    layer1_screen = lv_obj_create(NULL); // Create second clean base screen 
    layer2_screen = lv_obj_create(NULL);
    layer3_screen = lv_obj_create(NULL);
    // Attach to menu screen
    main_menu(layer0_screen);
    main_menu(layer1_screen);
    led_menu(layer2_screen);
    sound_board_menu(layer3_screen);
}

void lvgl_helper::brightness_display(lv_obj_t * parent) {
    led_brightness_label = lv_label_create(parent);
    lv_label_set_text(led_brightness_label, "LED Brightness: 100%");
    lv_obj_set_style_text_color(led_brightness_label, lv_color_hex(0x00FFCC), LV_PART_MAIN);
    lv_obj_set_pos(led_brightness_label, 150, 240);
}

void lvgl_helper::pattern_display(lv_obj_t * parent) {
    led_pattern_label = lv_label_create(parent);
    lv_label_set_text(led_pattern_label, "LED Pattern: Solid");
    lv_obj_set_style_text_color(led_pattern_label, lv_color_hex(0x00FFCC), LV_PART_MAIN);
    lv_obj_set_pos(led_pattern_label, 150, 270);
}

void lvgl_helper::btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target_obj(e);
    uint8_t to_change = *(uint8_t*)lv_event_get_user_data(e);
    if(code == LV_EVENT_CLICKED) {
        total_init::layer_change(to_change);
    }
}

void lvgl_helper::check_layer_update() {
    // Local snapshot variables
    uint8_t current_snap = 0;
    uint8_t current_brightness = 0;
    uint8_t current_pattern = 0;
    const char* latest_song = NULL;
    bool lock_acquired = false;

    // 1. CRITICAL SECTION: Get data snapshots as fast as possible
    if (mutex_try_enter(&lvgl_mutex, NULL)) {
        current_snap = total_init::get_layer();
        current_brightness = total_init::get_brightness();
        current_pattern = total_init::get_led_pattern();
        
        // This just checks a flag/queue—keep it fast!
        total_init::update_song_display_check(); 
        latest_song = total_init::get_song(); 
        
        mutex_exit(&lvgl_mutex); // Lock released in microseconds!
        lock_acquired = true;
    }

    // 2. RENDERING SECTION: Do heavy UI work completely unlocked
    if (lock_acquired) {
        if(current_snap == 2) {
            if(led_brightness_label != NULL && lv_obj_is_valid(led_brightness_label)) {
                if(current_brightness != last_brightness) {
                    last_brightness = current_brightness;
                    char brightness_text[32];
                    // snprintf happens safely OUTSIDE the lock
                    snprintf(brightness_text, sizeof(brightness_text), "LED Brightness: %d%%", current_brightness);
                    lv_label_set_text(led_brightness_label, brightness_text);
                }
            }

            if(led_pattern_label != NULL && lv_obj_is_valid(led_pattern_label)) {
                if(current_pattern != last_led_pattern) {
                    last_led_pattern = current_pattern;
                    lv_label_set_text(led_pattern_label, led_patterns[current_pattern].c_str());
                }
            }
        }

        if ((current_snap == 0 || current_snap == 1) && latest_song != NULL) {    
            lv_obj_t * active_song_label = song_labels[current_snap];
            if (active_song_label != NULL) {
                const char* current_ui_text = lv_label_get_text(active_song_label);
                // strcmp and layout engine manipulation happen completely unlocked
                if (strcmp(current_ui_text, latest_song) != 0) {
                    lv_label_set_text(active_song_label, latest_song);
                }
            }
        }
    }

    // 3. SCREEN LOAD MANAGMENT (Core 1 Local)
    uint8_t current = total_init::get_layer();
    if (current == previous) return;
    previous = current;

    switch(current) {
        case 0: lv_screen_load(layer0_screen); break;
        case 1: lv_screen_load(layer1_screen); break;
        case 2: lv_screen_load(layer2_screen); break;
        case 3: lv_screen_load(layer3_screen); break;
    }
}