//
// Created by per on 12/30/22.
//
#include "uiastdlib.h"
#include "display.h"

class OperatingSystem{
    UiAOS::IO::VGA display;


public:
    OperatingSystem(vga_color color)
            : display(color){

    }

    void init(){
        display.print_string("Initializing UiA Operating System....");
        display.print_new_line();
    }

    void debug_print(char* str){
        display.print_string(str);
        display.print_new_line();
    }

};


extern "C" void kernel_main()
{
    // Create operating system object
    auto os = OperatingSystem(RED);
    os.init();

    // Do some printing!
    os.debug_print("Hello World!");

    // Do some non-standard itoa
    char str_num[4];
    itoa(1337, str_num);

    asm volatile ("int $0x3");
    // Should not print the number!


    // Print that number.
    os.debug_print(str_num);
}
