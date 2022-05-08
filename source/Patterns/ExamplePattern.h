#pragma once
#include "Pattern.h"

class ExamplePattern : public Pattern{

    public:
        using Pattern::Pattern;
        void run();
        void init();
        void release();

};