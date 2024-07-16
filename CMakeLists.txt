# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
   set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(PICO_SDK_PATH ${USERHOME}/.pico-sdk/sdk/1.5.1)
set(PICO_TOOLCHAIN_PATH ${USERHOME}/.pico-sdk/toolchain/13_2_Rel1)
if(WIN32)
    set(pico-sdk-tools_DIR ${USERHOME}/.pico-sdk/tools/1.5.1)
    include(${pico-sdk-tools_DIR}/pico-sdk-tools-config.cmake)
    include(${pico-sdk-tools_DIR}/pico-sdk-tools-config-version.cmake)
endif()
# ====================================================================================
cmake_minimum_required(VERSION 3.13)

# optionally initialize pico_sdk from GIT
# (note this can come from environment, CMake cache etc)
# set(PICO_SDK_FETCH_FROM_GIT on)

# pico_sdk_import.cmake is a single file copied from this SDK
# note: this must happen before project()
include(pico_sdk_import.cmake)




# This is only for pico w
message("Running makefsdata python script")
execute_process(COMMAND
    python3 makefsdata.py
    WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

# Define ARM_CPU, CMSIS ROOT and DSP to use CMSIS-DSP
set(ARM_CPU "cortex-m0plus")
set(PICO_BOARD pico_w) # Remove for just normal pico
set(ROOT ${CMAKE_CURRENT_LIST_DIR}/source/kylarLEDs/Controllers/Sensors/Microphone/pdm_mic/CMSIS_5)
set(DSP ${ROOT}/CMSIS/DSP)


project(firefly)

# initialize the Pico SDK
pico_sdk_init()


#include_directories(firefly PRIVATE ${CMAKE_CURRENT_LIST_DIR})
#include_directories(firefly PRIVATE /Users/kylar/projects/pico-sdk/lib/lwip/src/include)
# include_directories(firefly PRIVATE /Users/kylar/projects/pico-sdk/lib/lwip/src/include/lwip/arch)
# include_directories(firefly PRIVATE /Users/kylar/projects/firefly-led-framework/include)


# include CMSIS-DSP .cmake for GCC Toolchain
include(${DSP}/Toolchain/GCC.cmake)

# add CMSIS-DSP Source directory as subdirectory
add_subdirectory(${DSP}/Source EXCLUDE_FROM_ALL)



file(GLOB_RECURSE SRCSCPP source/*.cpp)
file(GLOB_RECURSE SRCSC source/*.c)
file(GLOB_RECURSE HDRS source/*.h)


list(APPEND ALL_SOURCES ${SRCSCPP} ${SRCSC} ${HDRS})
list(FILTER ALL_SOURCES EXCLUDE REGEX /CMSIS_5/) # Exclude CMSIS files, they have their own CMAKE stuff above
#message(STATUS "Include dir: ${ALL_SOURCES}")

add_executable(firefly
    ${ALL_SOURCES}
    # ${SRCSCPP}
    # ${SRCSC}
    # ${HDRS}
)


target_include_directories(firefly PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
)



target_link_libraries(  firefly 
                        pico_stdlib 
                        pico_multicore 
                        hardware_pio 
                        hardware_adc 
                        hardware_dma 
                        hardware_irq 
                        CMSISDSPTransform 
                        CMSISDSPSupport 
                        CMSISDSPCommon 
                        CMSISDSPComplexMath 
                        CMSISDSPFastMath 
                        CMSISDSPBasicMath
                        pico_cyw43_arch_lwip_poll # pico w only
                        pico_lwip_http # pico w only
)



# enable usb output, disable uart output
pico_enable_stdio_usb(firefly 1)
pico_enable_stdio_uart(firefly 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(firefly)