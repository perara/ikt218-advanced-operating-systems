set(OS_SDK_MODULE_MUSL_NAME ${OS_KERNEL_NAME}-sdk-musl)
set(OS_SDK_MODULE_MUSL_TARGET sdk-${OS_KERNEL_NAME}-musl)


FetchContent_Declare(
        musl
        URL https://musl.libc.org/releases/musl-1.2.3.tar.gz
)
FetchContent_MakeAvailable(musl)

function(find_musl_files)
    file(GLOB OS_SDK_MODULE_MUSL_LIBRARIES ${musl_BINARY_DIR}/lib/*.a)
    file(GLOB OS_SDK_MODULE_MUSL_OBJECTS ${musl_BINARY_DIR}/lib/*.o)
    file(GLOB_RECURSE OS_SDK_MODULE_MUSL_SOURCES ${musl_SOURCE_DIR}/src/*.c)

    set(OS_SDK_MODULE_MUSL_INCLUDE_DIR ${musl_BINARY_DIR}/include PARENT_SCOPE)
    set(OS_SDK_MODULE_MUSL_LIBRARIES ${OS_SDK_MODULE_MUSL_LIBRARIES} PARENT_SCOPE)
    set(OS_SDK_MODULE_MUSL_OBJECTS ${OS_SDK_MODULE_MUSL_OBJECTS} PARENT_SCOPE)
    set(OS_SDK_MODULE_MUSL_SOURCES ${OS_SDK_MODULE_MUSL_SOURCES} PARENT_SCOPE)

endfunction()

find_musl_files()


if (NOT DEFINED OS_SDK_MODULE_MUSL_LIBRARIES)
    execute_process(
            COMMAND bash -c "CC=${gcc-path} ./configure --disable-shared --enable-debug --prefix=${musl_BINARY_DIR} && make -j && make install"
            WORKING_DIRECTORY ${musl_SOURCE_DIR}

    )
endif()
find_musl_files()

add_library(${OS_SDK_MODULE_MUSL_NAME} OBJECT ${OS_SDK_MODULE_MUSL_OBJECTS}) # ${OS_SDK_MODULE_MUSL_SOURCES}
set_target_properties(
        ${OS_SDK_MODULE_MUSL_NAME} PROPERTIES
        LINKER_LANGUAGE C
)
target_link_libraries(
        ${OS_SDK_MODULE_MUSL_NAME}
        PUBLIC
        ${OS_SDK_MODULE_MUSL_LIBRARIES}
        gcc # TODO - Is this good?
)

target_include_directories(${OS_SDK_MODULE_MUSL_NAME} PUBLIC ${OS_SDK_MODULE_MUSL_INCLUDE_DIR})

#target_link_libraries(${OS_SDK_MODULE_MUSL_NAME} INTERFACE ${OS_SDK_MODULE_MUSL_OBJECTS})
#

set(OS_SDK_MODULE_MUSL_NAME ${OS_SDK_MODULE_MUSL_NAME} PARENT_SCOPE)
set(OS_LIBRARIES ${OS_SDK_MODULE_MUSL_NAME} PARENT_SCOPE)