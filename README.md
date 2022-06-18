# kylarLEDs

## Welcome to the FireFlies LED Framework by kylarLEDs!

    The project uses a Raspberry Pi Pico on the kylarLEDs FireFly board!
    Eventually the project will be hardware agnostic, so it should work for anything!

    The sensors on the board are:
        1. Microphone (not yet supported) -> for sound reactive LEDs
        2. Potentiometer (not yet supported) -> for brightness control
        3. Rotary encoder (not yet supported) -> for color/hue control
        4. Rotary encoder button (not yet supported) -> for changing patterns

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
        a. https://www.mouser.com/ProductDetail/GCT/USB4125-GF-A-0190
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
		- 2022 also works!
        Download Pico SDK: https://github.com/raspberrypi/pico-sdk
        Set Pico SDK Path: setx PICO_SDK_PATH "..\..\pico-sdk" 
		- "..\..\" is just wherever you installed it, mine is "C:\pico\pico-sdk"
	Use visual studio code, get CMake Tools extension and configure project

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
    RP2040: https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf


## LED Library Architecture
### You are encouraged to add to and edit:
#### Patterns (user created)
    • Pattern object is parent, user creates subclasses
	• Patterns have logic to decide which Effects to start
        • Ex. using microphone data to spawn an effect
    • Patterns manage their effects and add them to the EffectEngine
    • Patterns do not directly write LEDs

#### Effects (user created)
	• Effect object is parent, user creates subclasses
	• Have LED write control
    • Use generators, LEDOutput

#### source/main.cpp (carefully)
    • You will need to add your patterns here for them to become selectable
    • You should only need to change 1 line per pattern
    • Just add a line under "ADD YOUR PATTERNS HERE!"

### You do not need to worry about:
#### LED Interface (library)
	• HW independent
	• Manages LEDs, count, current values, conversions
    • Calls upon controller object to output
    • Everything is normalized to 1.0 (this makes life easier)
        • Fixed vs Floating performance is negligible from my quick test4
	• HSV/RGB support
    • Adaptive framerate based on furthest LED index updated
    • 1 interface per strip output

#### Effect Engine (library)
	• Manage all effects
	• Combine every loop
	• Output using LED output

#### Controller functionality (library)
	• Hue, brightness, pattern change
	• Contains the way that LED output is handled on the lowest level
    • Also allows Sensors to connect somehow

#### Sensors library (library)
	• Microphone
        • This requires a lot of processing power for FFT/PDM
    • Potentiometer
    • Encoder
    • Encoder Button
    • Future Sensor ideas:
        • Accel/Gyro
        • Temp/Humidity
        • Magnetic Sensor


#### Generators (library)
	• Time dependent sin/triangle waves
    • Noise functions (perlin )



## KylarLEDs idea pad:
### I want to benchmark different ways of doing the LEDInterface
    Is it better to have an static array, dynamically allocated array, or a vector for keeping track of LEDChange objects. Maybe a map?
        - I'd be interested in timing the different implementations
        - Maybe I should add some sort of timing interface to easily do this :)

    For the LEDChange objects, how should the combining be done? Simple average, or should there be a more complex way of combining overlapping colors?

### Introduce LED objects, and a linked list of LED objects
    It would be nice to be able to order LED is certain ways, kind of like a "virtual strip." Having a linkedlist is just the first step, but like the Dome this would expand to being able to make a graph of LEDs.


### Noise/color functions in the generator
    Everyone seems to like perlin noise for cool color maps on grids/strips of LEDs
    Imagine the generator can also support more color gradients that can be linearly scrolled through.
    Is the generator class going to exist on its own, or will it have children? In that case, do the children have access to the static member "controller"?

### List of things still need to add:
    Support for multiple strips / multiple LED interfaces
    FireFlys example pattern
    Dynamic strip lengths - no predefined length
    Controller Hue control
    Controller Pattern button
    Make a CMakeFile for the targeted controller to keep CMake hw agnostic
    Add execution timing utility
    Make the Controller have a static variable for the current controller in use
    Rename "Examples" for effects to "Basic" and have like single led fades and use them for fireflys
    Have Basics be various Single LED stuff, and also various "streamers"
    Make sure memory is being removed when doing done=1
    Check EffectEngine clear() / rework what release() does
    Add simple way to do gradients / time based HSV
    Also a time based brightness to replace doing it manually in SingleTime.cpp
    Make Encoder class not static - need to do the interrupts TODO
    Make Encoder counts scale based on how fast it is turning
    Fix interrupts - note "GPIO parameter is ignored, callback will be called for any enabled GPIO IRQ pin"
        - see "Button.cpp" initialization for more detail
    Detect high frequency output so that light doesn't flicker between brightness levels
    Make sensor classes Static?
    LEDInterface rework:
        -remove led interface from main, have it be created by patterns
        -instead of calling the leds apply and output from main, can be done in engine
        -patterns would make their own led interface object with specified # leds
        -controller need a way to change # leds, and save between power cycles
    Take out the "Single Time"'s timing profile and put it in the Timer utility
        -> This is so it can be used for both brightness and saturation
        -> Maybe also add a way to do color by time :) 
            -> Something like +0.001 / loop -> 0.0x / ms
            -> I guess this can already be done with the timer->everyMs(1) { hue+=0.01 } - but this could still be missed...
            -> need something that is like hue = timer->time()*0.01; // where Time() returns time in ms (double)
    Make scaling for color change knob. Turning faster changes hue more, turning slow changes hue less
        -> use this algo in the next note for strip lengths..
    Make ability to change strip lengths via encoder (hold down button for 3 seconds, then turn knob)
        -> note the note before this one, knob turn speed should make strip length adjust better
        -> the pico can detect "level_low" for detecting button held down.
    Make sleep mode when potentiometer is turned down below <0.02, see if pico has a wake up interrupt for this
    Make a way for LEDInterface to accept saturation changes?
        -> So if I want to only change the saturation of a pixel, regardless of what is there
        -> Hard part is that LEDChanges store RGB, because it is easier to combine
        -> But HSV is only way to mix Saturation. Maybe there is a native HSV mix function, and we convert to RGB only for output
    Make brightness change smooth.
    Detect brightness flickering (especially for low brightness when pot rests between two levels and the noise changes the level)
    Done:
        Have ADC sample for pots be time/interrupt based (60hz or something)
            Or have a poll time, so when it is moving it is more polled more
         Controller Brightness control

