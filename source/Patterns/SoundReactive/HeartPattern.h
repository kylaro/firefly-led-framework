#pragma once
#include "../Pattern.h"
#include "../../kylarLEDs/Utility/Timing.h"
#include "../../Effects/Images/Heart.h"

class HeartPattern : public Pattern{

    public:
        using Pattern::Pattern;
        void run();
        void init();
        void release();
        virtual ~HeartPattern();
        
    
    private:
        int initted = 0;
        Heart *heart;
        Timing *avgTimer;
        Timing *secTimer;
        Timing *valTimer;

        
        

};