/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>

#include <atomic>              
#include "pico/util/queue.h"   
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "total_init.h"
#include "ws2812.pio.h"
#include "ws2812.h"

#define IS_RGBW false
#define NUM_PIXELS 78

#ifdef PICO_DEFAULT_WS2812_PIN
#define WS2812_PIN PICO_DEFAULT_WS2812_PIN
#else
#define WS2812_PIN 22
#endif

#if WS2812_PIN >= NUM_BANK0_GPIOS
#error Attempting to use a pin>=32 on a platform that does not support it
#endif

// ====================================================================
// Implement the Ws2812Strip Class Methods inside the led_control namespace
// ====================================================================
namespace led_control {

    // 1. Class Initialization Method
    void Ws2812Strip::init() {
        stdio_init_all();
        printf("WS2812 Init, using pin %d\n", WS2812_PIN);

        this->pio_ = pio1;
        this->sm_ = 0;
        this->offset_ = 0;

        // FIXED: Explicitly cast variables to (uint*) to satisfy the compiler types
        bool success = pio_claim_free_sm_and_add_program_for_gpio_range(
            &ws2812_program, &this->pio_, (uint*)&this->sm_, (uint*)&this->offset_, WS2812_PIN, 1, true
        );
        hard_assert(success);

        ws2812_program_init(this->pio_, this->sm_, this->offset_, WS2812_PIN, 800000, IS_RGBW);
    }

    // 2. Pattern Snakes Method
    void Ws2812Strip::pattern_snakes(uint32_t t) {
        uint8_t dimmed_max = total_init::brightness_led(0xff);

        for (uint i = 0; i < NUM_PIXELS; ++i) {
            uint x = (i + (t >> 1)) % 64;
            if (x < 10) {
                this->put_pixel(urgb_u32(dimmed_max, 0, 0)); // FIXED: Class scoped helper calls
            }
            else if (x >= 15 && x < 25) {
                this->put_pixel(urgb_u32(0, dimmed_max, 0));
            }
            else if (x >= 30 && x < 40) {
                this->put_pixel(urgb_u32(0, 0, dimmed_max));
            }
            else {
                this->put_pixel(0);
            }
        }
    }

    // 3. Pattern Random Method
    void Ws2812Strip::pattern_random(uint32_t t) {
        if (t % 8) return;
        for (uint i = 0; i < NUM_PIXELS; ++i) {
            uint8_t r = total_init::brightness_led(rand() & 0xFF);
            uint8_t g = total_init::brightness_led(rand() & 0xFF);
            uint8_t b = total_init::brightness_led(rand() & 0xFF);
            this->put_pixel(urgb_u32(r, g, b));
        }
    }

    // 4. Pattern Sparkle Method
    void Ws2812Strip::pattern_sparkle(uint32_t t) {
        if (t % 8) return;
        uint8_t white_dimmed = total_init::brightness_led(0xff);
        
        for (uint i = 0; i < NUM_PIXELS; ++i) {
            if (rand() % 16 == 0) {
                this->put_pixel(urgb_u32(white_dimmed, white_dimmed, white_dimmed));
            } else {
                this->put_pixel(0);
            }
        }
    }

    // 5. Pattern Greys Method
    void Ws2812Strip::pattern_greys(uint32_t t) {
        uint max = 100;
        t %= max;
        for(uint i = 0; i < NUM_PIXELS; i++) {
            this->put_pixel(t * 0x10101);
            if (++t >= max) t = 0;
        }
    }

    // ====================================================================
    // Internal Class Private Helpers (Fulfilling the ws2812.h declaration)
    // ====================================================================
    void Ws2812Strip::put_pixel(uint32_t pixel_grb) {
        pio_sm_put_blocking(this->pio_, this->sm_, pixel_grb << 8u);
    }

    uint32_t Ws2812Strip::urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
        return ((uint32_t) (r) << 8) | ((uint32_t) (g) << 16) | (uint32_t) (b);
    }

    uint32_t Ws2812Strip::urgbw_u32(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
        return ((uint32_t) (r) << 8) | ((uint32_t) (g) << 16) | ((uint32_t) (w) << 24) | (uint32_t) (b);
    }

} // namespace led_control