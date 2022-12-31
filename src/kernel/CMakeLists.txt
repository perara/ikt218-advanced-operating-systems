########################################
###
### OS Module: stdlib
#  The UiA Standard C Library
#  Contains functions to build the OS.
########################################
add_subdirectory(src/modules/stdlib)


########################################
###
### OS Module: Display
# Module for supporting printing to the display/terminal
########################################
add_subdirectory(src/modules/io/display)


########################################
###
### Set configuration for Kernel Module
###
########################################
set(OS_MODULE_KERNEL_NAME ${OS_KERNEL_NAME}-kernel)
set(OS_MODULE_KERNEL_COMPILE_FLAGS )
file(GLOB_RECURSE OS_MODULE_KERNEL_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/system/*.cpp)

########################################
###
### Add executable for the kernel
###
########################################
add_library(${OS_MODULE_KERNEL_NAME} ${OS_MODULE_KERNEL_SOURCES})
target_include_directories(
        ${OS_MODULE_KERNEL_NAME} PUBLIC
        include
)

########################################
###
### Link libraries with the kernel.
### 1. Boot
########################################
message("Linking kernel with following libraries ${OS_LIBRARIES}")
target_link_libraries(
        ${OS_MODULE_KERNEL_NAME} PUBLIC
        ${OS_LIBRARIES}
        ${OS_APPLICATIONS}
)

########################################
###
### Export variables to parent_Scope
###
########################################
set(OS_MODULE_KERNEL_NAME ${OS_MODULE_KERNEL_NAME} PARENT_SCOPE)