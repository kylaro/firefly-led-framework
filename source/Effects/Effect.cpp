#include "Effect.h"

Effect::Effect(LEDInterface *LEDs){
    this->LEDs = LEDs;

}

int Effect::isDone(){
    return this->done;
}