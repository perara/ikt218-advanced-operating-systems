


if(ARCH_TARGET STREQUAL "i386")
    set(OS_MODULE_BOOT_NAME ${OS_KERNEL_NAME}-boot)


    set(OS_MODULE_BOOT_SOURCES
            ${ARCH_TARGET}/boot.asm
            src/boot.cpp
    )


    add_library(${OS_MODULE_BOOT_NAME} ${OS_MODULE_BOOT_SOURCES})
    target_include_directories(${OS_MODULE_BOOT_NAME} PUBLIC ${ARCH_TARGET}/ include)
    target_link_libraries(${OS_MODULE_BOOT_NAME} PRIVATE ${OS_MODULE_KERNEL_NAME} ${OS_LIBRARIES})

    set(OS_LIBRARIES ${OS_LIBRARIES} ${OS_MODULE_BOOT_NAME} PARENT_SCOPE)

else()
    message(FATAL_ERROR "No boot definition exists for ${ARCH_TARGET}")
endif()
