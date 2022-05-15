#pragma once
#include "../kylarLEDs/EffectEngine/EffectEngine.h"
#include "../kylarLEDs/LEDInterface/LEDInterface.h"


class Pattern {
    /*
        • Pattern object is parent, user creates subclasses
        • Patterns have logic to decide which Effects to start
            • Ex. using microphone data to spawn an effect
        • Patterns manage their effects and add them to the EffectEngine
        • Patterns do not directly write LEDs
    */
    public:
        Pattern(LEDInterface *);
        virtual void run() = 0;
        virtual void init() = 0;
        virtual void release() = 0;

    protected:
        LEDInterface *LEDs;
        int initialized = 0;
};
