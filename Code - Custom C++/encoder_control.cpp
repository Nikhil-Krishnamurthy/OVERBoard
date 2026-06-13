#include <cstdint>
#include "hardware/pio.h"
#include "hardware/gpio.h"
#include "encoder_control.h"
#include "encoder_actions.h"
#include "total_init.h"

encoder_control::encoder_control()
{

}

encoder_control::~encoder_control()
{

}

void encoder_control::init_encoder(uint8_t a, uint8_t b, uint8_t id){
     _pinA = a;
    _pinB = b;
    _id = id;
}

void encoder_control::scan_ind(){
    // Inside individual_encoder.cpp (or inside your class update method)
    // 1. Read the physical pins assigned to THIS specific instance
    bool currentA = gpio_get(_pinA);
    bool currentB = gpio_get(_pinB);

    encoder_actions::thud_scan();

    // 2. Check if Phase A just changed state (A transition occurred)
    if (currentA != _lastA) {
        
        // If Pin A is different from Pin B, it's spinning Clockwise. 
        // If they match, it's spinning Counter-Clockwise.
        bool clockwise = (currentA != currentB);
        
        // 3. Fire the action instantly using your clean system!
        encoder_actions::handle_turn(_id, clockwise, total_init::get_layer());
    }

    // Save the state for the next loop sweep
    _lastA = currentA;
}
