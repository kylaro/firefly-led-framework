#pragma once
#include "../Controller.h"
#include "rp2040_pio.h"

class FireFlyController : public Controller{
    public:
        FireFlyController();
        //using Controller::Controller;
        void outputLEDs(uint8_t *leds, uint32_t N); // leds is an array, N is the length
        uint32_t getCurrentTimeMillis();
    protected:
        void initCommunication();
        void initHue(); // Change hue via encoder
        void initBrightness(); // Change the brightness via potentiometer
        void initPatternButton(); // Change the patternIndex via button press
        void initOutput();
    private:
        uint8_t PX_pin = 17;
        uint8_t PX_sm = 0;
        PIO PX_pio = pio0;
};