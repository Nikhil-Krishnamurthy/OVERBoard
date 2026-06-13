#ifndef uart_control_H
#define uart_control_H

#pragma once

class uart_control
{
public:
    uart_control();
    ~uart_control();
    static void uart_init_custom();
    static void broadcast_layer(uint8_t layer);
    static void uart_read_inputs();
private:

};

#endif