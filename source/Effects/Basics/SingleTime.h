#pragma once
#include "../Effect.h"
#include "../../kylarLEDs/Utility/Timing.h"
//Single LED, time-based brightness

typedef struct{
    int index;
    double hue;
    double brightness;
    uint32_t Toffset;
    uint32_t Trise;
    uint32_t Thold;
    uint32_t Tfall;
} single_time_t; // Times are in milliseconds

class SingleTime : public Effect{

    public:
        using Effect::Effect;
        void run();
        void init();
        SingleTime* init(single_time_t blueprint);
        void release();
    private:
        single_time_t profile;
        Timing *timer = NULL;

};


/*
x = time (milliseconds)
y = brightness      Trise     Thold
    |     |->       ->|->     ->|
1   |                xxxxxxxxxxx
    |              xx           xx
    |            xx               xx
0.5 |          xx                   xx
    |        xx                       xx
    |      xx                           xx
0   |xxxxxx                               xx___
    |   ->|                    |->       ->|
         Toffset                         Tfall


    |Toffset->Trise->Thold->Tfall
    
*/