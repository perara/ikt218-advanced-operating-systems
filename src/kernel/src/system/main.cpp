//
// Created by per on 12/30/22.
//

#include "uiastdlib.h"
#include "display.h"

extern "C" {
    #include <stdio.h>
    #include <stdlib.h>
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
    #include <hardware.h>
}


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

    void interrupt_handler_3(registers_t regs){
        display.print_string("Called Interrupt Handler 3!");
        display.print_new_line();
    }

    void interrupt_handler_4(registers_t regs){
        display.print_string("Called Interrupt Handler 4!");
        display.print_new_line();
    }


    int lua_example(){
        // TODO - This will not work - Our kernel is far from strong enough!
        lua_State* L;

        /* initialize Lua */
        L = luaL_newstate();
        luaL_openlibs(L);

        lua_pushstring(L, "0.7");
        lua_setglobal(L, "VERSION");


        /* get number of arguments */
        int n = lua_gettop(L);
        double sum = 0;
        int i;

        /* loop through each argument */
        for (i = 1; i <= n; i++)
        {
            if (!lua_isnumber(L, i))
            {
                lua_pushstring(L, "Incorrect argument to 'average'");
                lua_error(L);
            }

            /* total the arguments */
            sum += lua_tonumber(L, i);
        }

        /* push the average */
        lua_pushnumber(L, sum / n);

        /* push the sum */
        lua_pushnumber(L, sum);

        /* return the number of results */
        return 2;
    }

};

extern "C" void kernel_main()
{

    // Create operating system object
    auto os = OperatingSystem(RED);
    os.init();

    register_interrupt_handler(3,[](registers_t regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->interrupt_handler_3(regs);
    }, (void*)&os);

    register_interrupt_handler(4,[](registers_t regs, void* context){
        auto* os = (OperatingSystem*)context;
        os->interrupt_handler_4(regs);
    }, (void*)&os);



    // Do some printing!
    os.debug_print("Hello World!");

    // Do some non-standard itoa
    char str_num[4];
    itoa(1337, str_num);

    asm volatile ("int $0x3");
    // Should not print the number!
    asm volatile ("int $0x4");

    // Print that number.
    os.debug_print(str_num);
}
