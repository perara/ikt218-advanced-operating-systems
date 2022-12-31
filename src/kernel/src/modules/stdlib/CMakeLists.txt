



set(OS_MODULE_STDLIB_NAME ${OS_KERNEL_NAME}-module-stdlib)
set(OS_MODULE_STDLIB_SOURCES
    uiastdlib.cpp
)

add_library(${OS_MODULE_STDLIB_NAME} ${OS_MODULE_STDLIB_SOURCES})
target_include_directories(${OS_MODULE_STDLIB_NAME} PUBLIC
        .
)
target_link_libraries(${OS_MODULE_STDLIB_NAME} PUBLIC
        ${OS_LIBRARIES}
)


set(OS_LIBRARIES ${OS_LIBRARIES} ${OS_MODULE_STDLIB_NAME} PARENT_SCOPE)