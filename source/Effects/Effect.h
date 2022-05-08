#pragma once
#include "../kylarLEDs/LEDInterface/LEDInterface.h"

class Effect {
    /*
        • Effect object is parent, user creates subclasses
        • Have LED write control
        • Use generators, LEDOutput
    */
    public:
        Effect();
        virtual void run();
        virtual void init();
        virtual void release();

        LEDInterface *LEDs;
};
