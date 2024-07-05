#pragma once
#include "stdint.h"

//#include "HAIntegration.h"
#include "Network.h"


class MQTT{
    public:
        MQTT();
        static void start();
    private:
        static int initialized;
        //HAIntegration integration;


};