#pragma once
#include "Controller.h"

class FireFlyController : public Controller{

    public:
        FireFlyController();
        //using Controller::Controller;
        void outputLEDs(uint32_t *leds, uint32_t N); // leds is an array, N is the length
    protected:
        void initCommunication();
        void initHue(); // Change hue via encoder
        void initBrightness(); // Change the brightness via potentiometer
        void initPatternButton(); // Change the patternIndex via button press
};