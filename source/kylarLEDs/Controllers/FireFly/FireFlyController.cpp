#include "FireFlyController.h"
#include "pico/stdlib.h"
#include "hardware/dma.h"
#include <stdio.h>
#include "pico/time.h"

FireFlyController::FireFlyController()
{
    initCommunication();
    initBrightness();
    initHue();
    initPatternButton();
    initMicrophone();
    initOutput();

    this->timing = new Timing();
}

void FireFlyController::initDMA(PIO pio, uint sm)
{
}

void FireFlyController::initOutput()
{

    // initDMA();

    uint offset = pio_add_program(pio, &ws2812_program);
    // Init 4 strips
    for (uint8_t i = 0; i < PX_PINS; i++)
    {
        strips[i].pin = PX_pins[i];
        strips[i].sm = PX_sms[i];
        strips[i].dma_chan = dma_claim_unused_channel(true);

        uint8_t PX_pin = PX_pins[i];
        gpio_init(PX_pin);
        gpio_set_dir(PX_pin, GPIO_OUT);
        gpio_put(PX_pin, 0);

        uint8_t PX_sm = PX_sms[i];
        // 800kHz, 8 bit transfers
        ws2812_program_init(pio, strips[i].sm, offset, strips[i].pin, 800000, 8);
    }

}

void FireFlyController::initCommunication()
{
    int LED_PIN = 25; // Built-in LED pin
    stdio_init_all();
    // Initialize built-in LED
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    for (int i = 0; i < 10; i++)
    {
        gpio_put(LED_PIN, 1);
        sleep_ms(20);
        gpio_put(LED_PIN, 0);
        sleep_ms(20);
    }

    printf("Communication established\n");

    // // How to overclock (or underclock!)
    // if (!set_sys_clock_khz(250000, false)){
    //   printf("system clock 250MHz failed\n");
    // }else{
    //   printf("system clock now 250MHz\n");
    // }
}

uint64_t FireFlyController::getCurrentTimeMicros()
{
    absolute_time_t new_time = get_absolute_time(); // Microseconds
    uint64_t micros = new_time;
    return micros;
}

uint64_t FireFlyController::getCurrentTimeMillis()
{
    absolute_time_t new_time = get_absolute_time(); // Microseconds
    uint64_t millis = new_time / 1000;
    return millis;
}

void FireFlyController::outputLEDs(uint8_t strip, uint8_t *leds, uint32_t N)
{
    uint32_t numBytes = N * 3;
    uint8_t *pixels = leds;
    // uint32_t bytes[numBytes];
    //  This is only necessary to format data, but later can change to this being how it is inputted
    for (int i = 0; i < numBytes; i++)
    {
        strips[strip].outPointer[i] = ((uint32_t)pixels[i]) << 24;
    }
    int sm = strips[strip].sm;
    int dma_chan = strips[strip].dma_chan;

    dma_channel_config c = dma_channel_get_default_config(dma_chan);
    channel_config_set_read_increment(&c, true);
    channel_config_set_write_increment(&c, false);
    channel_config_set_dreq(&c, pio_get_dreq(pio, sm, true));
    channel_config_set_transfer_data_size(&c, DMA_SIZE_32);
    dma_channel_configure(dma_chan, &c,
                          &pio->txf[sm],            // Destination pointer
                          strips[strip].outPointer, // Source pointer
                          numBytes,                 // Number of transfers
                          true                      // Start immediately
    );

  
    // while(numBytes--){
    //     // Bits for transmission must be shifted to top 8 bits
    //     pio_sm_put_blocking(PX_pio, strip, ((uint32_t)*pixels++)<< 24);
    // }
    // sleep_ms(1);
}

double FireFlyController::getBrightness()
{
    static double brightness = 0;
    static double lastPot = 0;
    if (timing->takeMsEvery(10))
    {
        double newPot = analogPot->getValue();
        brightness = (lastPot * 400 + newPot) / 401.0;
        lastPot = (lastPot * 2.0 + newPot) / 3.0;
    }
    else
    {
        return brightness;
    }
    brightness = brightness * brightness * brightness;
    return brightness;
}

double FireFlyController::getHue()
{
    int count = encoder->getCount();
    double hue = (count) / 360.0;
    return hue;
}

void FireFlyController::initHue()
{
    encoder = new Encoder(26, 22);
}

void FireFlyController::initBrightness()
{
    this->analogPot = new Potentiometer(27, 1);
}

void FireFlyController::initPatternButton()
{
    this->button = new Button(28);
}

void FireFlyController::givePatternIndex(uint32_t *patternIndex)
{
    this->patternIndex = patternIndex;
    Button::givePatternIndex(this->patternIndex);
}

void FireFlyController::initMicrophone()
{
    Microphone::start();
}