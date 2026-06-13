#ifndef SONG_INFO_H
#define SONG_INFO_H

#pragma once
#define MAX_MESSAGE_LENGTH 128

class song_info
{
public:
    song_info();
    ~song_info();
    static bool scan_info();
    static void check_buffer();

private:
    static char message[MAX_MESSAGE_LENGTH];
    static bool message_recieved;
    static unsigned int message_pos;
    static char inByte;
};

#endif