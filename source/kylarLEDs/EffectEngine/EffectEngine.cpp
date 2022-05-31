#include "EffectEngine.h"
#include <stdio.h>
#include <cstdlib>
EffectEngine::EffectEngine(){

}

void EffectEngine::clear() {
    printf("clear\n");
    for (Effect* eff : effects) {
        printf("release\n");
        eff->release();
        printf("released\n");
        free(eff);
    }
    for (Effect* eff : effectsQueue){
        printf("freeing effect queue");
        eff->release();
        free(eff);
    }
    printf("run\n");
    //run();
    printf("ran\n");
    printf("clear the rest\n");
    effects.clear();
    effectsQueue.clear();
    printf("cleared the rest\n");
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
    printf("got iterator\n");
    while (it != effects.end())
    {
        printf("actually enterred the loop\n");
        Effect* effect = *it;
        printf("dereferenced iterator*\n");
        if (effect->isDone()) {
            printf("isdone\n");
            // erase() invalidates the iterator, use returned iterator
            effect->release();
            printf("release\n");
            it = effects.erase(it);
            printf("erase\n");
            free(effect);
            printf("free\n");
            continue;
        } else {
            printf("about to run\n");
            effect->run();
            printf("effect ran\n");
            it++;
            printf("it++\n");
        }
        
    }
    printf("moved on\n");
    for (Effect* eff : effectsQueue) {
        printf("there was stuff in the queue\n");
        effects.push_back(eff);
    }
    effectsQueue.clear();
    printf("finished effect engine\n");
}