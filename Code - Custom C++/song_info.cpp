#include <stdio.h>
#include "pico/stdlib.h"
#include "tusb.h"
#include "total_init.h"
#include "lvgl_helper.h"
#include "song_info.h"
#define MAX_MESSAGE_LENGTH 128

unsigned int song_info::message_pos = 0;
char song_info::message[MAX_MESSAGE_LENGTH];
char song_info::inByte;

song_info::song_info()
{

}

song_info::~song_info()
{

}

void song_info::check_buffer(){
    if(tud_cdc_available()){
        scan_info();
    }
}

bool song_info::scan_info(){
//Check to see if anything is available in the serial receive buffer
while (tud_cdc_available())
{
//Read the next available byte in the serial receive buffer
inByte = tud_cdc_read_char();
//Message coming in (check not terminating character) and guard for over message size
if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
{
//Add the incoming byte to our message
message[message_pos] = inByte;
message_pos++;
}
//Full message received...
else
{
//Add null character to string
message[message_pos] = '\0';
total_init::set_song(message);
//Reset for the next message
message_pos = 0;
}
}
return 0;
}
