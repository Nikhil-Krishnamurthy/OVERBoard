#ifndef ENCODER_MANAGER_H
#define ENCODER_MANAGER_H

#pragma once
#include <array>
#include "encoder_control.h"

class encoder_manager
{
public:
    encoder_manager();
    ~encoder_manager();
    static void init_encoders();
    static void scan_encoders();
private:
    inline static std::array<encoder_control, 3> encoders;
};

#endif