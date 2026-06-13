#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/i2c.h"
#include "hardware/pio.h"
#include "hardware/uart.h"
#include "pico/multicore.h"
#include "lvgl_helper.h"

#include "lvgl-master/lvgl.h"
#include "ili9341.h"

#include "total_init.h"
#include "uart_control.h"
#include "spi_control.h"
#include "i2c_control.h"
#include "encoder_manager.h"
#include "song_info.h"

#define TFT_HOR_RES 320
#define TFT_VER_RES 240

uint32_t current_time = 0;
uint32_t ellapsed_time = 0;


static uint32_t my_tick_cb(void)
{
    return to_ms_since_boot(get_absolute_time());
}

static void my_flush_cb(lv_display_t * disp, const lv_area_t * area, uint8_t * px_map)
{
    /*Write px_map to the area->x1, area->x2, area->y1, area->y2 area of the
     *frame buffer or external display controller. */
    uint16_t w = (area->x2 - area->x1) + 1;
    uint16_t h = (area->y2 - area->y1) + 1;

    // 2. Cast the raw uint8_t byte pointer to a 16-bit pointer (RGB565) 
    // because your driver handles 16-bit pixel data blocks
    uint16_t * bitmap = (uint16_t *)px_map;

    // 3. Pass everything directly into your hardware driver function
    LCD_WriteBitmap(area->x1, area->y1, w, h, bitmap);
    /* signal LVGL that we're done */
    lv_display_flush_ready(disp);
}

/*static void my_touch_read_cb(lv_indev_t * indev, lv_indev_data_t * data)
{
   if(my_touch_is_pressed()) {
       data->point.x = touchpad_x;
       data->point.y = touchpad_y;
       data->state = LV_INDEV_STATE_PRESSED;
   } else {
       data->state = LV_INDEV_STATE_RELEASED;
   }
}*/

void core1_loop()
{
    total_init::total_init_core1();
    /*Initialize LVGL*/
    lv_init();

    /*Set millisecond-based tick source for LVGL so that it can track time.*/
    lv_tick_set_cb(my_tick_cb);

    /*Create a display where screens and widgets can be added*/
    lv_display_t * display = lv_display_create(TFT_HOR_RES, TFT_VER_RES);

    /*Add rendering buffers to the screen.
     *Here adding a smaller partial buffer assuming 16-bit (RGB565 color format)*/
    static uint16_t buf1[TFT_HOR_RES * TFT_VER_RES / 10]; /* x2 because of 16-bit color depth */
    static uint16_t buf2[TFT_HOR_RES * TFT_VER_RES / 10];
    lv_display_set_buffers(display, buf1, buf2, sizeof(buf1), LV_DISPLAY_RENDER_MODE_PARTIAL);

    /*Add a callback that can flush the content from `buf` when it has been rendered*/
    lv_display_set_flush_cb(display, my_flush_cb);

    /*Create an input device for touch handling*/
    //lv_indev_t * indev = lv_indev_create();
    //lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    //lv_indev_set_read_cb(indev, my_touch_read_cb);

    lvgl_helper::init_all_ui_views();

    /*Execute the LVGL-related tasks in a loop*/
    
    while(1) {
    lv_timer_handler_run_in_period(5);
    lvgl_helper::check_layer_update();
}
}

int main(){
    // --- STEP 1: INITIALIZATION (Runs on Core 0) ---
    stdio_init_all();
    
    // Core 0 sets up the shared song queue, I2C, and UART
    total_init::total_init_core0();
    
    // Core 0 sets up the input encoders
    encoder_manager::init_encoders();

    // --- STEP 2: LAUNCH CORE 1 ---
    // Now that everything in memory is ready, wake up Core 1!
    multicore_launch_core1(core1_loop); 

    // --- STEP 3: CORE 0 MAIN LOOP ---
    // This main loop now belongs exclusively to Core 0
    while(1){
        encoder_manager::scan_encoders();
        song_info::check_buffer();
        total_init::check_failure();
        total_init::check_layer();
        uart_control::uart_read_inputs();
    }

    return 0; // The compiler is happy, but we never reach this
}