#pragma once
#include "../Controllers/Controller.h"
#include "ColorUtil.h"
#include "LEDChange.h"

#define NUM_LEDS 20

class LEDInterface{
    /*
	• HW independent
	• Manages LEDs, count, current values, conversions
    • Calls upon controller object to output
    • Everything is normalized to 1.0 (this makes life easier)
        • Fixed vs Floating performance is negligible from my quick test4
	• HSV/RGB support
    • Adaptive framerate based on furthest LED index updated
    */

    public:
        LEDInterface();
        void apply();   // Apply the changes 
        void output();  // and output
        void setRGB(int index, rgb_t rgb);
        void setHSV(int index, hsv_t hsv);
        void giveController(Controller *);
    private:
        Controller * ledController;
        LEDChange* changesArray[NUM_LEDS]; // Need to update this length or make it dynamic!!
        uint8_t ledsArray[NUM_LEDS*3];
};