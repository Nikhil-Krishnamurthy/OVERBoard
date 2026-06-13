#ifndef ENCODER_CONTROL_H
#define ENCODER_CONTROL_H

#pragma once

class encoder_control
{
public:
    encoder_control();
    ~encoder_control();
    void scan_ind();
    void init_encoder(uint8_t a, uint8_t b, uint8_t id);

private:
    uint8_t _pinA;
    uint8_t _pinB;
    uint8_t _id;
    uint8_t _lastA;
};

#endif