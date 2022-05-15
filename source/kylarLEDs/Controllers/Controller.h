#pragma once
#include <stdint.h>

class Controller {
    public:
        Controller();
        void givePatternIndex(uint32_t *patternIndex);
        virtual void outputLEDs(uint8_t *leds, uint32_t N) = 0; // leds is an array, N is the length
        virtual double getHue();
        virtual double getBrightness();
        virtual uint64_t getCurrentTimeMillis() = 0;
    protected:
        uint32_t *patternIndex = 0;
        double hue = 0;
        double brightness = 0.5;
        virtual void initCommunication() = 0;
        virtual void initHue() = 0; // Change hue via encoder
        virtual void initBrightness() = 0; // Change the brightness via potentiometer
        virtual void initPatternButton() = 0; // Change the patternIndex via button press
        // virtual void savePatternHue(); // Save pattern hue via file 
        // virtual double loadPatternHue(); // Load pattern hue via file 
        // virtual void savePatternIndex(); // Save pattern index via file
        // virtual void loadPatternIndex(); // Save pattern index via file during init
};