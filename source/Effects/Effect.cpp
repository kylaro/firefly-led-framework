#include "Effect.h"

EffectEngine* Effect::engine;
Effect::Effect(LEDInterface *LEDs){
    this->LEDs = LEDs;
}

int Effect::isDone(){
    return this->done;
}

//static
void Effect::giveEngine(EffectEngine * effectEngine){
    Effect::engine = effectEngine;
}