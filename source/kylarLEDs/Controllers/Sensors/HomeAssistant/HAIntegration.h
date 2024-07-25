#ifndef HAINTEGRATION_H
#define HAINTEGRATION_H

extern "C" {
    #include "ha_mqtt.h"
}

class HAIntegration {
    public:
        HAIntegration();
        void connect();
        void configure();
        void loop();

        bool getEnabled();
};

#endif // HAINTEGRATION_H
