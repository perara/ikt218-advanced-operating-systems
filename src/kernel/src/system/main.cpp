//
// Created by per on 12/30/22.
//

extern "C" void kernel_main()
{
    char* video_memory = (char*) 0xb8000;
    *video_memory = 3; // Should print a heart

}