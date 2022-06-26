#pragma once
#include "../Controllers/Controller.h"
#include "ColorUtil.h"
#include "LEDChange.h"
#include "../../config.h"


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
        LEDInterface(uint8_t strip);
        void apply();   // Apply the changes 
        void output();  // and output
        void clear();   // clear
        void setRGB(int index, rgb_t rgb);
        void setRGBUnprotected(int index, rgb8_t rgb); // can use if getting the rgb from setHSV
        irgb8_t setHSV(int index, hsv_t hsv);
        void giveController(Controller *);
        double num(); //Get number of LEDs
        void setNum(uint16_t num); //set number of LEDs
    private:
        Controller * ledController;
        LEDChange* changesArray[NUM_LEDS]; // Need to update this length or make it dynamic!!
        
        uint8_t ledsArray[NUM_LEDS*(3+RGBW)]; // 3 bytes per LED, plus 1 byte if RGBW
        uint16_t numLEDs = NUM_LEDS;
        

        uint8_t strip = 0;
};