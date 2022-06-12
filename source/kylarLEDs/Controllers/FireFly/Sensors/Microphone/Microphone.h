#pragma once
#include "stdint.h"
extern "C" {
    #include "pdm_mic/audio_spectrogram.h"
}


class Microphone{
    public:
        Microphone();
        static void start();
    private:
        static int count;
        static int frequency;

};