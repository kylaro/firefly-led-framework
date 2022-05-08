#pragma once
#include "../Controllers/Controller.h"

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
        void run();   // Apply the changes and output
        void setRGB();
        void setHSV();
        void giveController(Controller *);

    private:
        Controller * ledController;
};