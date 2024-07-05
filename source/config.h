#pragma once

#define NUM_STRIPS 2    // This should honestly be a bit mask (0000 1010) would be strips 1 and 3
#define NUM_LEDS 64 // this is per strip

#define LOW_BINS 20
#define SKIP_BINS 0
#define DEBUG_PRINT 1
#define OVERCLOCK 0 // set clock to 250MHz instead of 125MHz

// Choose only 1 of these:
#define MICROPHONE_ENABLE 0
#define WIFI_ENABLE 0 // picow only. (not implemented)
#define MQTT_ENABLE 1 // picow only.