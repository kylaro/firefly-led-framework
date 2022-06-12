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

# Define ARM_CPU, CMSIS ROOT and DSP to use CMSIS-DSP
set(ARM_CPU "cortex-m0plus")
set(ROOT ${CMAKE_CURRENT_LIST_DIR}/source/kylarLEDs/Controllers/FireFly/Sensors/Microphone/pdm_mic/CMSIS_5)
set(DSP ${ROOT}/CMSIS/DSP)

# include CMSIS-DSP .cmake for GCC Toolchain
include(${DSP}/Toolchain/GCC.cmake)

# add CMSIS-DSP Source directory as subdirectory
add_subdirectory(${DSP}/Source EXCLUDE_FROM_ALL)


file(GLOB_RECURSE SRCSCPP source/*.cpp)
file(GLOB_RECURSE SRCSC source/*.c)
file(GLOB_RECURSE HDRS source/*.h)

list(APPEND ALL_SOURCES ${SRCSCPP} ${SRCSC} ${HDRS})
list(FILTER ALL_SOURCES EXCLUDE REGEX /CMSIS_5/) # Exclude CMSIS files, they have their own CMAKE stuff above
# message(STATUS "foo include dir: ${ALL_SOURCES}")

add_executable(firefly
    ${ALL_SOURCES}
    # ${SRCSCPP}
    # ${SRCSC}
    # ${HDRS}
)

# add_executable(firefly
#     ${CMAKE_CURRENT_LIST_DIR}/source/main.cpp
# )




target_link_libraries(firefly pico_stdlib pico_multicore hardware_pio hardware_adc hardware_dma CMSISDSPTransform CMSISDSPSupport CMSISDSPCommon CMSISDSPComplexMath CMSISDSPFastMath CMSISDSPBasicMath)

# enable usb output, disable uart output
pico_enable_stdio_usb(firefly 1)
pico_enable_stdio_uart(firefly 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(firefly)