


set(OS_SDK_MODULE_LUA_NAME ${OS_KERNEL_NAME}-sdk-lua)


FetchContent_Declare(
        lua
        URL http://www.lua.org/ftp/lua-5.4.4.tar.gz
        URL_HASH MD5=bd8ce7069ff99a400efd14cf339a727b
)
FetchContent_MakeAvailable(lua)


file(GLOB LUA_SOURCES ${lua_SOURCE_DIR}/src/*.c)
#set(LUA_SOURCES
#        ${lua_SOURCE_DIR}/src/lua.c
#        ${lua_SOURCE_DIR}/src/luac.c
#    )


add_library(${OS_SDK_MODULE_LUA_NAME}  ${LUA_SOURCES})
target_link_libraries(${OS_SDK_MODULE_LUA_NAME}
        PRIVATE
        ${OS_SDK_MODULE_MUSL_NAME}
)
target_include_directories(
        ${OS_SDK_MODULE_LUA_NAME}
        PUBLIC
        ${lua_SOURCE_DIR}/src
)
#set_target_properties(
#        ${OS_SDK_MODULE_LUA_NAME} PROPERTIES
#        LINK_FLAGS " -T ${CMAKE_SOURCE_DIR}/src/arch/i386/linker.ld -ffreestanding -O2 -nostdlib -lgcc"
#)

set(OS_APPLICATIONS ${OS_APPLICATIONS} ${OS_SDK_MODULE_LUA_NAME} PARENT_SCOPE)

