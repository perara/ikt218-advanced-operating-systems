########################################
###
### OS Module: stdlib
#  The UiA Standard C Library
#  Contains functions to build the OS.
###
########################################
add_subdirectory(stdlib)

########################################
###
### OS Module: Display
# Module for supporting printing to the display/terminal
###
########################################
add_subdirectory(io/display)

set(OS_LIBRARIES ${OS_LIBRARIES} PARENT_SCOPE)