#pragma once
#include "stdint.h"
#include "../../../../Utility/Timing.h"
extern "C" {
    #include "driver/scd41_basic.h"
}


class CO2{
    public:
        CO2();
        static void start();
        static double getCO2();
        static Timing *timing;
        
    private:
        static int initialized;
        

};