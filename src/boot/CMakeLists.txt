


if(ARCH_TARGET STREQUAL "i386")
    set(OS_MODULE_BOOT_NAME ${OS_KERNEL_NAME}-boot)
    set(OS_MODULE_BOOT_COMPILE_OPTS -m32 -elf -dbg)


    set(OS_MODULE_BOOT_SOURCES
            ${ARCH_TARGET}/boot.s
    )

    add_library(${OS_MODULE_BOOT_NAME} OBJECT ${OS_MODULE_BOOT_SOURCES})
    target_compile_options(${OS_MODULE_BOOT_NAME} PUBLIC ${OS_MODULE_BOOT_COMPILE_OPTS})
    target_link_libraries(${OS_MODULE_BOOT_NAME} PRIVATE ${OS_LIBRARIES})
    target_include_directories(${OS_MODULE_BOOT_NAME} PUBLIC ${ARCH_TARGET}/)

    set(OS_LIBRARIES ${OS_LIBRARIES} ${OS_MODULE_BOOT_NAME} PARENT_SCOPE)
else()
    message(FATAL_ERROR "No boot definition exists for ${ARCH_TARGET}")
endif()
