#pragma once
#include "../kylarLEDs/EffectEngine/EffectEngine.h"

class Pattern {
    /*
        • Pattern object is parent, user creates subclasses
        • Patterns have logic to decide which Effects to start
            • Ex. using microphone data to spawn an effect
        • Patterns manage their effects and add them to the EffectEngine
        • Patterns do not directly write LEDs
    */
    public:
        Pattern();
        virtual void run();
        virtual void init();
        virtual void release();

        EffectEngine *effectEngine;
};
