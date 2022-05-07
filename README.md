# kylarLEDs

## Welcome to the FireFly LED Controller by kylarLEDs!

    The project uses a Raspberry Pi Pico on the kylarLEDs FireFly board!

    The sensors on the board are:
        1. Microphone (not yet supported) -> for sound reactive LEDs
        2. Rotary encoder (not yet supported) -> for color/hue control
        3. Potentiometer (not yet supported) -> for brightness control

    The outputs from the board are:
        1. 2 x WS2812B LED output pins (not yet supported)
            a. Each pin has 2 output pads, one on front and one on back
            b. Each pin has a 0.1 inch header port
        2. 2 x USBC 5V power up to 3A

    The input to the boards are:
        1. Pico programming micro usb port (not meant for power)
        2. 1 x USBC 5V power up to 3A

## Quick start
### You don't want the source, you just want to put it on your Pico
    1. Go to the build folder and get the "firefly.uf2" file.
    2. Follow instructions for "Upload to Pico"


## Components
    1. Pico
        a. https://vilros.com/products/raspberry-pi-pico
    2. Potentiometer
        a. https://www.mouser.com/ProductDetail/652-PTV09A-4020FB104
    3. Encoder
        a. https://www.mouser.com/ProductDetail/652-PEC12R-4020F-S24
    4. USBC
        a. https://www.mouser.com/ProductDetail/GCT/USB4125-GF-A-0190?qs=QNEnbhJQKvbCz4hEJBS24w%3D%3D
    5. PDM Mic
        a. https://www.mouser.com/ProductDetail/CUI-Devices/CMM-4737DT-26186-TR
    6. Resistors - 0805 10K Ohm (for Encoder)
        a. https://www.mouser.com/ProductDetail/Xicon/260-10K-RC
    7. Capacitors - 0805 0.10 uF (for Encoder)
        a. https://www.mouser.com/ProductDetail/KEMET/C0805C104M5RAC


## Windows:
    Getting started:
    https://www.electronicshub.org/programming-raspberry-pi-pico-in-windows/

    Getting started TLDR:
        Download ARM Compiler: https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/downloads
        Download CMake: https://cmake.org/download/
        Download VS Build tools: https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2019
        Download Pico SDK: https://github.com/raspberrypi/pico-sdk
        Set Pico SDK Path: setx PICO_SDK_PATH "..\..\pico-sdk"


    Building Cmake projects for Pico:
        1. Clone the whole git repo
        2. Open a "Developer command prompt for VS 2019"
        3. Navigate to the cloned repo
        4. cd build
        5. cmake -G "NMake Makefiles" .. 
        6. nmake

    Upload to Pico:
        1. Hold "boot select" button on Pico
        2. Plug into Computer (while button is held)
        3. The pico should show up the same way a USB drive does
        4. Drag "firefly.uf2" into the Pico filesystem
        5. The pico will restart and begin running your code


## Pico Documentation:
    SDK: https://raspberrypi.github.io/pico-sdk-doxygen/index.html
    C: https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf



