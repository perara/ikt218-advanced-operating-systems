


if(ARCH_TARGET STREQUAL "i386")
    set(OS_MODULE_BOOT_LINKER ${CMAKE_SOURCE_DIR}/src/arch/${ARCH_TARGET}/linker.ld)
    set(OS_MODULE_BOOT_NAME ${OS_KERNEL_NAME}-boot)
    set(OS_MODULE_BOOT_COMPILE_OPTS -m32 -elf -dbg)
    set(OS_MODULE_BOOT_LINK_FLAGS "-T ${OS_MODULE_BOOT_LINKER} -m32 -ffreestanding -O2 -nostdlib -lgcc")
    set(OS_MODULE_BOOT_BINARY ${OS_KERNEL_NAME}.bin)


    set(OS_MODULE_BOOT_SOURCES
            ${ARCH_TARGET}/boot.s
    )

    add_executable(${OS_MODULE_BOOT_NAME} ${OS_MODULE_BOOT_SOURCES})
    target_compile_options(${OS_MODULE_BOOT_NAME} PUBLIC ${OS_MODULE_BOOT_COMPILE_OPTS})
    target_link_libraries(${OS_MODULE_BOOT_NAME} PRIVATE ${OS_MODULE_KERNEL_NAME} ${OS_LIBRARIES})
    target_include_directories(${OS_MODULE_BOOT_NAME} PUBLIC ${ARCH_TARGET}/)

    set(OS_LIBRARIES ${OS_LIBRARIES} ${OS_MODULE_BOOT_NAME} PARENT_SCOPE)

    ########################################
    ###
    ### Set name and linker flags for the kernel
    ###
    ########################################
    set_target_properties(
            ${OS_MODULE_BOOT_NAME} PROPERTIES
            OUTPUT_NAME ${OS_MODULE_BOOT_BINARY}
            LINK_FLAGS " ${OS_MODULE_BOOT_LINK_FLAGS}"
    )

else()
    message(FATAL_ERROR "No boot definition exists for ${ARCH_TARGET}")
endif()
