#pragma once
#include "../Controller.h"
#include "rp2040_pio.h"
#include "Sensors/Potentiometer/Potentiometer.h"
#include "Sensors/Encoder/Encoder.h"
#include "Sensors/Button/Button.h"
#include "Sensors/Microphone/Microphone.h"
#include "../../Utility/Timing.h"

class FireFlyController : public Controller{
    public:
        FireFlyController();
        //using Controller::Controller;
        void outputLEDs(uint8_t *leds, uint32_t N); // leds is an array, N is the length
        uint64_t getCurrentTimeMillis();
        uint64_t getCurrentTimeMicros();
        double getHue();
        double getBrightness();
        void givePatternIndex(uint32_t *patternIndex);
    protected:
        void initCommunication();
        void initHue(); // Change hue via encoder
        void initBrightness(); // Change the brightness via potentiometer
        void initPatternButton(); // Change the patternIndex via button press
        void initOutput();
        void initMicrophone();
    private:
        uint8_t PX_pin = 17; // 16 for 1, 17 for 2
        uint8_t PX_sm = 0;
        PIO PX_pio = pio0;

        Potentiometer *analogPot;
        Encoder *encoder;
        Timing *timing;
        Button *button;
        Microphone *microphone;
};