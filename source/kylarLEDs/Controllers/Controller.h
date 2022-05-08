#pragma once
#include <stdint.h>

class Controller {
    public:
        Controller();
        void givePatternIndex(uint32_t *patternIndex);
        int value = 9;
    protected:
        uint32_t *patternIndex = 0;
        virtual void initCommunication();
};