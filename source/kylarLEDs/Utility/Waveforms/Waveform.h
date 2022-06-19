#pragma once
#include "../Timing.h"
#include <stdlib.h>
class Waveform {
    public:
        Waveform();
        Waveform(uint32_t periodMs);
        ~Waveform();
        double value(); // Get current value
        virtual double sample(double index) = 0; // Grab a sample (0 to 1 continous range)
        void setPeriodMs( uint32_t period); // Set period of the waveform (1 full wave time)
        int complete(); // return how many times it has completed the wave
    protected:
        Timing *timer = NULL;
        void initTimer();
        uint32_t period = 1000;

};