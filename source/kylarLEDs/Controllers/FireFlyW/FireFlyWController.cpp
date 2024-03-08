#include "FireFlyWController.h"
#include "pico/stdlib.h"
#include "hardware/dma.h"
#include "hardware/irq.h"
#include <stdio.h>
#include "pico/time.h"
#include "../../../config.h"

uint64_t FireFlyWController::channel_end_times[NUM_STRIPS];
strip_t FireFlyWController::strips[NUM_STRIPS];
FireFlyWController::FireFlyWController()
{
    initCommunication();
    initBrightness();
    initHue();
    initPatternButton();
    if(MICROPHONE_ENABLE){
        initMicrophone();
    }
    initOutput();

    this->timing = new Timing();
}

void FireFlyWController::initDMA(PIO pio, uint sm)
{

}

// Used in interrupt
void FireFlyWController::handleDMA()
{
    //Loops through the strips and checks if the channel is done. If it is, it sets the channel_end_times to the current time.
    uint8_t dma_chan;
    for(int i = 0; i < NUM_STRIPS; i++){
        dma_chan = strips[i].dma_chan;
        if(dma_channel_get_irq1_status(dma_chan)){
            dma_channel_acknowledge_irq1(dma_chan);
            channel_end_times[i] = get_absolute_time();
        }

    }

}

void FireFlyWController::initOutput()
{
    
    // initDMA();

    uint offset = pio_add_program(pio, &ws2812_program);
    irq_set_exclusive_handler(DMA_IRQ_1, &FireFlyWController::handleDMA);
    irq_set_enabled(DMA_IRQ_1, true);
    // Init 4 strips
    for (uint8_t i = 0; i < PX_PINS; i++)
    {
        strips[i].pin = PX_pins[i];
        strips[i].sm = PX_sms[i];
        strips[i].dma_chan = dma_claim_unused_channel(true);
        dma_channel_set_irq1_enabled(strips[i].dma_chan, true);
        uint8_t PX_pin = PX_pins[i];
        gpio_init(PX_pin);
        gpio_set_dir(PX_pin, GPIO_OUT);
        gpio_put(PX_pin, 0);

        uint8_t PX_sm = PX_sms[i];
        // 800kHz, 8 bit transfers
        ws2812_program_init(pio, strips[i].sm, offset, strips[i].pin, 800000, 8);
    }

    // Make an array to flip bits for output
    uint8_t b;
    for(int i = 0; i < 256; i++){
        b = i;
        b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
        b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
        b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
        bitflipLUT[i] = b;
    }

}

void FireFlyWController::initCommunication()
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

uint64_t FireFlyWController::getCurrentTimeMicros()
{
    absolute_time_t new_time = get_absolute_time(); // Microseconds
    uint64_t micros = new_time;
    return micros;
}

uint64_t FireFlyWController::getCurrentTimeMillis()
{
    absolute_time_t new_time = get_absolute_time(); // Microseconds
    uint64_t millis = new_time / 1000;
    return millis;
}

void FireFlyWController::outputLEDs(uint8_t strip_i, uint8_t *leds, uint32_t N)
{
    uint32_t numBytes = N * 3; // N is numLEDs, which each require 3 bytes
    uint8_t *pixels = leds;
    strip_t *strip = &(strips[strip_i]);

    int sm = strip->sm;
    int dma_chan = strip->dma_chan;
    dma_channel_wait_for_finish_blocking(dma_chan);
    // add a 200 us wait here, because the led strip needs a reset after each write
    // This will be skipped if the strip had already been finished for long enough
    // Therefore the performance will not be affected
    int64_t diff = 0;
    while((diff = absolute_time_diff_us(channel_end_times[strip_i], get_absolute_time())) < 200){
        // The condition is checking the difference between the current time and the last time the channel was finished.
    }

    // uint32_t bytes[numBytes];
    //  This is only necessary to format data, but later can change to this being how it is inputted
    uint8_t b;
    for (int i = 0; i < numBytes; i++)
    {
        // Bit reverse for 4000 LEDs = LEDs::output() = 2282 us
        // BitflipLUT for 4000 LEDs = LEDs::output() = 1202 us
        strip->outPointer[i] = bitflipLUT[pixels[i]];
        //strip->outPointer[i] = ((uint32_t)pixels[i]) << 24; // Old method
    }
    

    dma_channel_config c = dma_channel_get_default_config(dma_chan);
    channel_config_set_read_increment(&c, true);
    channel_config_set_write_increment(&c, false);
    channel_config_set_dreq(&c, pio_get_dreq(pio, sm, true));
    channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
    dma_channel_configure(dma_chan, &c,
                          &pio->txf[sm],            // Destination pointer
                          strip->outPointer,        // Source pointer
                          numBytes,                 // Number of transfers
                          true                      // Start immediately
    );

  
    // while(numBytes--){
    //     // Bits for transmission must be shifted to top 8 bits
    //     pio_sm_put_blocking(PX_pio, strip, ((uint32_t)*pixels++)<< 24);
    // }
}

double FireFlyWController::getBrightness()
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

double FireFlyWController::getHue()
{
    int count = encoder->getCount();
    double hue = (count) / 360.0;
    return hue;
}

void FireFlyWController::initHue()
{
    encoder = new Encoder(26, 22);
}

void FireFlyWController::initBrightness()
{
    this->analogPot = new Potentiometer(27, 1);
}

void FireFlyWController::initPatternButton()
{
    this->button = new Button(28);
}

void FireFlyWController::givePatternIndex(uint32_t *patternIndex)
{
    this->patternIndex = patternIndex;
    Button::givePatternIndex(this->patternIndex);
}

void FireFlyWController::initMicrophone()
{
    Microphone::start();
}