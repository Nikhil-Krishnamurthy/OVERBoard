#include <stdio.h>
#include "pico/stdlib.h"
#include "encoder_actions.h"
#include "hardware/uart.h"
#include "uart_control.h"

#define UART_TX_PIN 0
#define UART_RX_PIN 1
#define BAUD_RATE 115200
#define UART_ID uart0

const uint8_t commands[] = {0x80, 0x81, 0x82, 0x83};

uart_control::uart_control()
{

}

uart_control::~uart_control()
{

}

void uart_control:: uart_init_custom(){
    //Initialize uart
    uart_init(UART_ID, BAUD_RATE);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
}

void uart_control::broadcast_layer(uint8_t layer){
    uart_write_blocking(UART_ID, &commands[layer], 1);
}

void uart_control::uart_read_inputs(){
    while(uart_is_readable(UART_ID)){
        uint8_t data = uart_getc(UART_ID);
        // Process the received data
        switch(data){
            case 0x79:
                // Handle enter screen command
                encoder_actions::enc3_physical_button_pressed = true;
                break;
            case 0x7A:
                // Handle release command
                encoder_actions::enc3_physical_button_pressed = false;
                break;
            default:
                // Handle unknown command
                break;
        }
    }
}