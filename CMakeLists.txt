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

########################################
###
### OS Module: musl-libc
# Build the musl libc
########################################
add_subdirectory(src/sdk/musl)

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

