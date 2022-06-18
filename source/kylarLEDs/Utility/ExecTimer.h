#pragma once
#include "stdint.h"
#include <time.h>
#include "../Controllers/Controller.h"
#include <map>
#include <string>
#include "Timing.h"
class ExecTimer {

    public:
        ExecTimer();
        ~ExecTimer();
        void print();
        void add(const char*);
        void start(const char*);
        double fps(); // print fps since start
    private:
        std::map<const char*, int> times;
        char *name;
        Timing *timer;
        uint64_t lastTime;
};