#include "EffectEngine.h"
#include <stdio.h>
#include <cstdlib>
EffectEngine::EffectEngine(){

}

void EffectEngine::clear() {
    for (Effect* eff : effects) {
        eff->release();
        free(eff);
    }
    for (Effect* eff : effectsQueue){
        eff->release();
        free(eff);
    }
    effects.clear();
    effectsQueue.clear();
}

void EffectEngine::apply(Effect *effect) {
	effects.push_back(effect);
}

void EffectEngine::queueApply(Effect *effect) {
    effectsQueue.push_back(effect);
}

void EffectEngine::run() {
    // This function essentially just calls run on every effect
    // It will also remove the effects that are "done"
    std::vector<Effect *>::iterator it = effects.begin();
    while (it != effects.end())
    {
        Effect* effect = *it;
        if (effect->isDone()) {
            // erase() invalidates the iterator, use returned iterator
            effect->release();
            it = effects.erase(it);
            free(effect);
            continue;
        } else {
            effect->run();
            it++;
        }
        
    }
    for (Effect* eff : effectsQueue) {
        effects.push_back(eff);
    }
    effectsQueue.clear();
}