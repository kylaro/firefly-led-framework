#pragma once
#include "stdint.h"
#include "pico/stdlib.h"
#include "pico/time.h"
class Encoder{
    public:
        Encoder(int A, int B);
        static int getCount();
        static void interrupt(uint gpio, uint32_t event);
    private:
        static uint8_t pinA;
        static uint8_t pinB;
        static int count;
        static int frequency;
        static bool frequencyReduce(struct repeating_timer *t);
};