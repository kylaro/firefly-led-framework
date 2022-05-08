#pragma once
#include "Controller.h"

class FireFlyController : public Controller{

    public:
        FireFlyController();
    protected:
        void initCommunication();
};