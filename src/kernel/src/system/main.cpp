//
// Created by per on 12/30/22.
//
#include "uiastdlib.h"



extern "C" void kernel_main()
{
    // Now we can use itoa!
    char str_num[1];
    itoa(9, str_num);

    char* video_memory = (char*) 0xb8000;
    *video_memory = str_num[0]; // Should print 9
}