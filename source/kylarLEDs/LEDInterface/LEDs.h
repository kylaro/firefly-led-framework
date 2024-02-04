#pragma once
#include "LEDInterface.h"
#include <stdint.h>
#include <vector>
class LEDs {
    public:
        LEDs();
        static LEDInterface *strip(uint8_t strip);
        static void init(uint8_t strips);
        static void output();// Outputs all strips via the controller
        static void clear(); // Clears all strips RGB values
        static void apply(); // Applies all of the changes from the effects for all strips
        static void setNum(uint16_t num); // Sets all LED strip lengths
        static void setHSV(int i, hsv_t color);// Sets HSV for an LED on all strips
        static void setRGB(int i, rgb8_t color);// Sets HSV for an LED on all strips
        static void giveController(Controller * controller); // give the strips the controller reference
    private:
        static std::vector<LEDInterface*> *strips;
        
};