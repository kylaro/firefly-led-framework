cmake_minimum_required(VERSION 3.12)

# optionally initialize pico_sdk from GIT
# (note this can come from environment, CMake cache etc)
# set(PICO_SDK_FETCH_FROM_GIT on)

# pico_sdk_import.cmake is a single file copied from this SDK
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(firefly-led-controller)

# initialize the Pico SDK
pico_sdk_init()

file(GLOB_RECURSE SRCS source/*.cpp)
file(GLOB_RECURSE HDRS source/*.h)

add_executable(firefly
    #${CMAKE_CURRENT_LIST_DIR}/source/main.cpp
    ${SRCS}
    ${HDRS}
)




target_link_libraries(firefly pico_stdlib)

# enable usb output, disable uart output
pico_enable_stdio_usb(firefly 1)
pico_enable_stdio_uart(firefly 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(firefly)