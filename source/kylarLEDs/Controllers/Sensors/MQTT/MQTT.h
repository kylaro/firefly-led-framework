#pragma once
#include "stdint.h"



class MQTT{
    public:
        MQTT();
        static void start();
    private:
        static int initialized;

};