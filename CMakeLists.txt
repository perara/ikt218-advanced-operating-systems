########################################
###
### The University of Agder Operating System
### We will be using C, C++ and Assembler
########################################
cmake_minimum_required(VERSION 3.24)
project(UiAOS LANGUAGES C CXX ASM)

########################################
###
### Configure Operating System
###
########################################
#set(ARCH_TARGET x86_64) #i386
set(ARCH_TARGET i386)
set(OS_NAME "UiA Operating System")
set(OS_KERNEL_NAME "uia-os")
set(OS_APPLICATIONS)
set(OS_LIBRARIES)

########################################
###
### Compiler path configuration
# We are using cross-compilation to ensure that the binary are compatible on other computers
# Arch: yay -S i386-elf-gcc
########################################
find_program(gcc-path ${ARCH_TARGET}-elf-gcc)
find_program(g++-path ${ARCH_TARGET}-elf-g++)

if(NOT ${gcc-path} STREQUAL ${CMAKE_C_COMPILER})
    message("Requires ${gcc-path} as compiler, but CMAKE_C_COMPILER=${CMAKE_C_COMPILER}")
    set(CMAKE_C_COMPILER   ${gcc-path})
endif()
if(NOT ${g++-path} STREQUAL ${CMAKE_CXX_COMPILER})
    message("Requires ${gcc-path} as compiler, but CMAKE_C_COMPILER=${CMAKE_CXX_COMPILER}")
    set(CMAKE_CXX_COMPILER ${g++-path})
endif()

########################################
###
### Set Compiler Flags
###
########################################
set (WARNING_FLAGS -Wall -Wextra -Wshadow -Wconversion -Wsign-conversion -Wno-error=unknown-warning)
set (COMMON_COMPILER_FLAGS -ffreestanding -fstack-protector-all ${WARNING_FLAGS})
set (C_COMPILER_FLAGS ${COMMON_COMPILER_FLAGS})
set (CXX_COMPILER_FLAGS ${COMMON_COMPILER_FLAGS} -fno-exceptions -fno-rtti -fconcepts)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_C_STANDARD 11)