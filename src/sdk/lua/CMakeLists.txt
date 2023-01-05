


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


add_library(${OS_SDK_MODULE_LUA_NAME} ${LUA_SOURCES})
target_link_libraries(${OS_SDK_MODULE_LUA_NAME}
        PRIVATE
        ${OS_LIBRARIES}


)
target_include_directories(
        ${OS_SDK_MODULE_LUA_NAME}
        PRIVATE
        ${COMMON_INCLUDE_PATHS}
        PUBLIC
        ${lua_SOURCE_DIR}/src
)
target_compile_options(
        ${OS_SDK_MODULE_LUA_NAME}
        PRIVATE ${COMMON_COMPILER_FLAGS}
)

set(OS_APPLICATIONS ${OS_APPLICATIONS} ${OS_SDK_MODULE_LUA_NAME} PARENT_SCOPE)

