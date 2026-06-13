#ifndef WS2812_H
#define WS2812_H

#include <cstdint>
#include "hardware/pio.h"

namespace led_control {

// Type-safe, scoped constants replacing preprocessor #defines
constexpr bool IS_RGBW = false;
constexpr uint32_t NUM_PIXELS = 78;
constexpr uint32_t WS2812_PIN = 22;

class Ws2812Strip {
public:
    //==========================================================================
    // Lifecycle & Initialization
    //==========================================================================
    Ws2812Strip() = default;
    ~Ws2812Strip() = default;

    void init();

    //==========================================================================
    // Public Animation Patterns
    //==========================================================================
    void pattern_snakes(uint32_t t);
    void pattern_random(uint32_t t);
    void pattern_sparkle(uint32_t t);
    void pattern_greys(uint32_t t);

    //==========================================================================
    // Hardware Getters
    //==========================================================================
    inline PIO get_pio() const { return pio_; }
    inline uint32_t get_sm() const { return sm_; }

private:
    //==========================================================================
    // Internal Utility Helpers
    //==========================================================================
    void put_pixel(uint32_t pixel_grb);
    uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b);
    uint32_t urgbw_u32(uint8_t r, uint8_t g, uint8_t b, uint8_t w);

    //==========================================================================
    // Private Hardware State Variables
    //==========================================================================
    PIO pio_ = pio1;
    uint32_t sm_ = 0;
    uint32_t offset_ = 0;
};

} // namespace led_control

#endif // WS2812_HPP