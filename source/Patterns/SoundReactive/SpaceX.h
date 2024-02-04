#pragma once
#include "../Pattern.h"
#include "../../kylarLEDs/Utility/Timing.h"
#include "../../Effects/Images/SpaceXLogo.h"

class SpaceX : public Pattern{

    public:
        using Pattern::Pattern;
        void run();
        void init();
        void release();
        virtual ~SpaceX();
        
    
    private:
        int initted = 0;
        SpaceXLogo *spacex_logo;
        Timing *avgTimer;
        Timing *secTimer;
        Timing *valTimer;

        
        

};