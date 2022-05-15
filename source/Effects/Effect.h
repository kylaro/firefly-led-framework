#pragma once
#include "../kylarLEDs/LEDInterface/LEDInterface.h"
#include "../kylarLEDs/EffectEngine/EffectEngine.h"
#include <cstdlib>
class EffectEngine;
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
        static void giveEngine(EffectEngine * effectEngine);
        static EffectEngine *engine;
        LEDInterface *LEDs;
        int isDone();
        int ID = -1;
    protected:
        int done = 0;
        int initialized = 0;
        
};
