




set(OS_MODULE_CPU_NAME ${OS_KERNEL_NAME}-cpu)
set(OS_MODULE_CPU_COMPILE_OPTS -m32 -elf -dbg)

set(OS_MODULE_CPU_SOURCES
        gdt.s
        gdt.c

        idt.s
        idt.c

        isr.c
        isr.s
)

add_library(${OS_MODULE_CPU_NAME} ${OS_MODULE_CPU_SOURCES})
target_compile_options(${OS_MODULE_CPU_NAME} PUBLIC ${OS_MODULE_CPU_COMPILE_OPTS})
target_link_libraries(${OS_MODULE_CPU_NAME} PRIVATE ${OS_MODULE_KERNEL_NAME} ${OS_LIBRARIES})
target_include_directories(${OS_MODULE_CPU_NAME} PUBLIC .)

set(OS_MODULE_CPU_NAME ${OS_KERNEL_NAME}-cpu PARENT_SCOPE)
set(OS_LIBRARIES ${OS_LIBRARIES} ${OS_MODULE_CPU_NAME} PARENT_SCOPE)