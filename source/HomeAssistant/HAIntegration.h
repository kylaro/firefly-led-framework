#ifndef HAINTEGRATION_H
#define HAINTEGRATION_H
#include "../kylarLEDs/Controllers/Controller.h"

class HAIntegration {
    public:
        HAIntegration(Controller* ledController);
        void connect();
        void configure();
        void loop();
    private:
        Controller* ledController;
};

#endif // HAINTEGRATION_H
