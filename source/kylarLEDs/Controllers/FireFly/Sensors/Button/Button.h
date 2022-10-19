#pragma once
#include "stdint.h"
#include "pico/stdlib.h"
extern "C" {
    #include "bootsel_button.h"
}
class Button{
    public:
        Button(int pin);
        static void givePatternIndex(uint32_t *patternIndex);
        static bool getBootselectButton();
    private:
        static uint8_t pin;
        static void interrupt(uint gpio, uint32_t event);
        static uint32_t *patternIndex;
};