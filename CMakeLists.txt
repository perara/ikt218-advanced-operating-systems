########################################
###
### The University of Agder Operating System
### We will be using C, C++ and Assembler
########################################
cmake_minimum_required(VERSION 3.24)
project(UiAOS LANGUAGES C CXX ASM_NASM)

########################################
###
### CMAKE Imports
###
########################################
include(FetchContent)

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
### Set Compiler and Linker FlagsFlags
###
########################################
set (WARNING_FLAGS -Wall -Wextra -Wshadow -Wconversion -Wsign-conversion)
set (COMMON_COMPILER_FLAGS -ffreestanding -O2)
set (C_COMPILER_FLAGS ${COMMON_COMPILER_FLAGS} ${WARNING_FLAGS})
set (CXX_COMPILER_FLAGS ${COMMON_COMPILER_FLAGS} ${WARNING_FLAGS} -fno-exceptions -fno-rtti)
set (ASM_COMPILER_FLAGS)
set (CXX_LINKER_FLAGS  "-nostdlib -ffreestanding")
set (COMMON_INCLUDE_PATHS /usr/include/)

message("CXX_COMPILER_FLAGS ${CXX_COMPILER_FLAGS}")
message("C_COMPILER_FLAGS ${C_COMPILER_FLAGS}")
message("ASM_COMPILER_FLAGS ${ASM_COMPILER_FLAGS}")





set (CMAKE_CXX_STANDARD 20)
set (CMAKE_C_STANDARD 99)



########################################
###
### Assembly configuration
# We use the nasm compiler
# And we must set the correct elf format
########################################
set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS ${CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS} s S)
if(ARCH_TARGET STREQUAL i386)
    set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
else()
    message(FATAL_ERROR "Currently, we do not support other than elf32")
endif()
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <DEFINES> <INCLUDES> <FLAGS> -f ${CMAKE_ASM_NASM_OBJECT_FORMAT} -o <OBJECT> <SOURCE>")

########################################
###
### OS Module: musl-libc
# Build the musl libc
########################################
add_subdirectory(src/sdk/musl)

########################################
###
### OS Module: lib
#  The UiA Standard C Library
#  Contains functions to build the OS.
###
########################################
add_subdirectory(src/stdlib)


########################################
###
### OS Module: lua
# Build the lua runtime
########################################
add_subdirectory(src/sdk/lua)

########################################
###
### OS Module: Boot
# The boot module takes care of booting the operating system
# it is written in assembler language and does the following
# 1. define the multiboot header variables
# 2. define the multiboot header section.
# 3. defines the .bss section. https://en.wikipedia.org/wiki/.bss
# 4. defines the .text section (code segment) https://en.wikipedia.org/wiki/Code_segment
# 5. defines the start routine which finally starts our kernel
########################################
add_subdirectory(src/boot)

########################################
###
### OS Module: Kernel
# The operating system kernel
# 1. Sets compiler and linker configuration
# 2. Locate and build sources of the kernel
# 3. Link boot object with the kernel
# 4. copy compiled binary to the root of the cmake build directory.
########################################
add_subdirectory(src/kernel)

########################################
###
### Grub
# Configure a bootable image of our operating system
########################################
add_subdirectory(src/grub)

########################################
###
### Create a CMAKE Target for QEMU
### QEMU is the virtual machine that we'll be using
### config/QEMURunner.sh.in is a template file which we will "fill in the blanks" using the below variables
########################################
set(QEMU_ARCH ${ARCH_TARGET})
set(QEMU_KERNEL_IMAGE ${GRUB_IMAGE_PATH})
set(QEMU_MEMORY 32)
set(QEMU_RUN_TARGET ${OS_KERNEL_NAME}-run)
set(QEMU_ARGS -daemonize)
configure_file(
        config/QEMURunner.sh.in QEMURunner.sh
        FILE_PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
add_custom_target(${QEMU_RUN_TARGET} COMMAND bash -c "${CMAKE_CURRENT_BINARY_DIR}/QEMURunner.sh")
add_dependencies(${QEMU_RUN_TARGET} ${GRUB_TARGET})

