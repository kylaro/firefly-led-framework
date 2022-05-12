#pragma once
#include "../Controllers/Controller.h"

typedef struct{
    double hue;         // Color: 0 to 1.0 : 0 is RED, 0.33 is GREEN, 0.66 BLUE
    double saturation;  // Whiteness: 0 to 1.0 : 0 is WHITE, 1 is COLOR
    double value;       // Brightness: 0 to 1.0 : 0 is OFF, 1 is ON
} hsv_t;

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
        void setHSV(int index, hsv_t hsv);
        void giveController(Controller *);

    private:
        Controller * ledController;
};