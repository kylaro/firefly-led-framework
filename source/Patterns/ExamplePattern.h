#pragma once
#include "Pattern.h"
#include "../kylarLEDs/Generators/Generator.h"

class ExamplePattern : public Pattern{

    public:
        using Pattern::Pattern;
        void run();
        void init();
        void release();
    
    private:
        Generator *myGenerator;
        

};