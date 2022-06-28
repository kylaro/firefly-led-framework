#pragma once
#include "../Effect.h"
#include "../../kylarLEDs/Utility/Waveforms/Waveform.h"
class WaveformLED : public Effect{

    public:
        WaveformLED(Waveform *waveform);
        ~WaveformLED();
        void run();
        void init();
        WaveformLED *setI(int i);
        WaveformLED *setCount(int count);
        WaveformLED *setHue(double hue);
        int i = 0;
        int count = 0;
        double hue = 0;
    private:
        int unused = 0;
        Waveform *wave;
};