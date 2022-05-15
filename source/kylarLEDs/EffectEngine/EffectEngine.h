#pragma once
#include "../../Effects/Effect.h"
#include <vector>
class Effect;
class EffectEngine{
    /*
        • Manage all effects
        • Combine every loop
        • Output using LED output
    */
    public:
        EffectEngine();
        void run();
        void clear();
        void apply(Effect *effect);
        void queueApply(Effect* effect);
        std::vector<Effect *> effects;
	    std::vector<Effect *> effectsQueue;
};