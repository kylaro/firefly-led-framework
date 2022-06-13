#pragma once
#include "stdint.h"
extern "C" {
    #include "pdm_mic/audio_spectrogram.h"
}

// This can be a static class (all funcs static)
// 
// Energy guide:
// Type of environment          | Low Val   | High Val  | Total Val
// Quiet office                 |   0       |   0       |   0
//      Clap 3 ft away          |
//      Blender in room         |   27      |   118     |   112
// Alien spaceship landing      |   1062    |   17      |   81
// Person talking about aliens  |   20      |   19      |   19
// Rap Billie Eilish (bass hit) |   1024    |   2       |   64
//                   (vocals)   |   14      |   6       |   7
// West Coast Wobble AmbientMax |   159     |   9       |   18
// West Coast Wobble AmbientMin |   0       |   9       |   9
// West Coast wobble amb range  |   40-150  |   4-9     |   4-14
// West Coast Wbl intense range |   14-76   |   3-10    |   4-18
class Microphone{
    public:
        Microphone();
        static void start();
        static double getFreqCenter();
        static double getHighFreqCenter();
        static double getLowFreqCenter();
        static double getEnergy();
        static double getLowEnergy();
        static double getHighEnergy();
        static double getLowNormal();
    private:
        static int count;
        static int frequency;

};