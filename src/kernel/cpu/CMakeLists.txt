

set(OS_MODULE_CPU_NAME ${OS_KERNEL_NAME}-cpu)
set(OS_MODULE_CPU_SOURCES
        ${ARCH_TARGET}/gdt.cpp
        ${ARCH_TARGET}/gdt_a.asm

        ${ARCH_TARGET}/idt.cpp
        ${ARCH_TARGET}/idt_a.asm

        ${ARCH_TARGET}/isr.cpp
        ${ARCH_TARGET}/isr_a.asm

        ${ARCH_TARGET}/hardware_port.cpp
        ${ARCH_TARGET}/hardware.cpp
        ${ARCH_TARGET}/timer/timer.cpp
)

add_library(${OS_MODULE_CPU_NAME} ${OS_MODULE_CPU_SOURCES})
target_link_libraries(${OS_MODULE_CPU_NAME} PRIVATE ${OS_MODULE_KERNEL_NAME} ${OS_LIBRARIES})
target_include_directories(${OS_MODULE_CPU_NAME} PUBLIC include)
target_compile_definitions(${OS_MODULE_CPU_NAME} PUBLIC
        ARCH_TARGET=${ARCH_TARGET}
)



set(OS_MODULE_CPU_NAME ${OS_KERNEL_NAME}-cpu PARENT_SCOPE)
set(OS_LIBRARIES ${OS_LIBRARIES} ${OS_MODULE_CPU_NAME} PARENT_SCOPE)