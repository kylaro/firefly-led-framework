#pragma once
#include "../Controller.h"
#include "rp2040_pio.h"
#include "../Sensors/Potentiometer/Potentiometer.h"
#include "../Sensors/Encoder/Encoder.h"
#include "../Sensors/Button/Button.h"
#include "../Sensors/Microphone/Microphone.h"
#include "../../Utility/Timing.h"

#define PX_PINS 4

typedef struct {
    uint8_t pin;
    uint8_t sm;
    uint8_t dma_chan;
    uint8_t outPointer[NUM_LEDS*3];
} strip_t;

class FireFlyWController : public Controller{
    public:
        FireFlyWController();
        //using Controller::Controller;
        void outputLEDs(uint8_t strip, uint8_t *leds, uint32_t N); // leds is an array, N is the length
        uint64_t getCurrentTimeMillis();
        uint64_t getCurrentTimeMicros();
        double getHue();
        double getBrightness();
        static void handleDMA();
        void givePatternIndex(uint32_t *patternIndex);
    protected:
        void initCommunication();
        void initHue(); // Change hue via encoder
        void initBrightness(); // Change the brightness via potentiometer
        void initPatternButton(); // Change the patternIndex via button press
        void initOutput();
        void initMicrophone();
    private:
        void initDMA(PIO pio, uint sm);
        
        static strip_t strips[NUM_STRIPS];
        uint8_t PX_pins[PX_PINS] = {16, 17, 8, 9};
        uint8_t PX_sms[PX_PINS] = {0, 1, 2, 3};
        uint8_t bitflipLUT[256];
        static uint64_t channel_end_times[NUM_STRIPS];
        
        //uint8_t PX_pin = 17; // 16 for 1, 17 for 2
        //uint8_t PX_sm = 0;
        PIO pio = pio0;
        //dma_channel_config *c;
        Potentiometer *analogPot;
        Encoder *encoder;
        Timing *timing;
        Button *button;
        Microphone *microphone;
};