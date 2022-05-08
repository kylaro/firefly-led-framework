#include "Controller.h"


Controller::Controller(){
    //I would like a way to put all the inits here
    // But they seem to need to be called in the derived class constructor :/
    // initCommunication();
    // initBrightness();
    // initHue();
    // initPatternButton();
}

void Controller::givePatternIndex(uint32_t *patternIndex){
    this->patternIndex = patternIndex;
}

double Controller::getHue(){
    return hue;
}

double Controller::getBrightness(){
    return brightness;
}