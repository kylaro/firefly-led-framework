#pragma once
#include "../kylarLEDs/LEDInterface/LEDInterface.h"

class Effect {
    /*
        • Effect object is parent, user creates subclasses
        • Have LED write control
        • Use generators, LEDOutput
    */
    public:
        Effect(LEDInterface *);
        virtual void run() = 0;
        virtual void init() = 0;
        virtual void release() = 0;
        LEDInterface *LEDs;
        int isDone();
    protected:
        int done = 0;
};
