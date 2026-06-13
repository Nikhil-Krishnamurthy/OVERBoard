#include <array> 
#include <cstdint>
#include "encoder_control.h"
#include "encoder_manager.h"

encoder_manager::encoder_manager()
{

}

encoder_manager::~encoder_manager()
{

}

void encoder_manager::init_encoders(){
    encoders[0].init_encoder(1, 1, 0);
    encoders[1].init_encoder(1, 1, 1);
    encoders[2].init_encoder(1, 1, 2);
}

void encoder_manager::scan_encoders(){
    encoders[0].scan_ind();
    encoders[1].scan_ind();
    encoders[2].scan_ind();
}