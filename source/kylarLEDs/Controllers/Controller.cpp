#include "Controller.h"


Controller::Controller(){
    initCommunication();
}

void Controller::givePatternIndex(uint32_t *patternIndex){
    this->patternIndex = patternIndex;
}


void Controller::initCommunication(){

    this->value = 72;
}