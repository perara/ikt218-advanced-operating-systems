//
// Created by per on 12/30/22.
//

#include "uiastdlib.h"
#include "driver.h"

extern "C" {
    #include <cpu.h>
    #include <stdio.h>
    #include <stdlib.h>
}


class OperatingSystem {
    int tick = 0;

public:
    OperatingSystem(vga_color color) {
        UiAOS::IO::Monitor::init_vga(WHITE, RED);

    }

    void init() {

        UiAOS::IO::Monitor::print_string("Initializing UiA Operating System....");
        UiAOS::IO::Monitor::print_new_line();
    }

    void debug_print(char *str) {
        UiAOS::IO::Monitor::print_string(str);
        UiAOS::IO::Monitor::print_new_line();
    }

    void interrupt_handler_3(registers_t regs) {
        UiAOS::IO::Monitor::print_string("Called Interrupt Handler 3!");
        UiAOS::IO::Monitor::print_new_line();
    }

    void interrupt_handler_4(registers_t regs) {
        UiAOS::IO::Monitor::print_string("Called Interrupt Handler 4!");
        UiAOS::IO::Monitor::print_new_line();
    }

    void timer() {
        tick++;
        if (tick % 100 == 0) {
            UiAOS::IO::Monitor::print_string("(Every Second) Tick: ");
            UiAOS::IO::Monitor::print_int(tick);
            UiAOS::IO::Monitor::print_new_line();
        }

    }
};

extern "C" void kernel_main()
{
    // Create operating system object
    auto os = OperatingSystem(RED);
    os.init();

    // Do some printing!
    os.debug_print("Hello World!");

    // Create some interrupt handlers for 3
    register_interrupt_handler(3,[](registers_t* regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->interrupt_handler_3(*regs);
    }, (void*)&os);

    // Create some interrupt handler for 4
    register_interrupt_handler(4,[](registers_t* regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->interrupt_handler_4(*regs);
    }, (void*)&os);


    // Fire interrupts! Should trigger callback above
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");

    // Print that number.
    os.debug_print("1337");


    // Disable interrutps
    asm volatile("sti");

    // Create a timer on IRQ0 - System Timer
    init_timer(1, [](registers_t*regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->timer();
    }, &os);



}

