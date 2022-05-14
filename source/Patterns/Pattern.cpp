#include "Pattern.h"


Pattern::Pattern(EffectEngine * effectEngine, LEDInterface * LEDs){
    this->effectEngine = effectEngine;
    this->LEDs = LEDs;
}