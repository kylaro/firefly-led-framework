#ifndef HAINTEGRATION_H
#define HAINTEGRATION_H

#include "HASwitch.h"

class HAIntegration {
    public:
    HAIntegration();
    void connect();
    void loop();
    void configure();
    static void switchHandler(bool state, HASwitch* sender);
};

#endif // HAINTEGRATION_H
