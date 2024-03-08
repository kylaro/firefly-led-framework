#pragma once
#include "stdint.h"
#include "pico/stdlib.h"
class Button{
    public:
        Button(int pin);
        static void givePatternIndex(uint32_t *patternIndex);
    private:
        static uint8_t pin;
        static void interrupt(uint gpio, uint32_t event);
        static uint32_t *patternIndex;
};