#include "HAIntegration.h"
#include "pico/time.h"
#include "pico/multicore.h"
#include "../kylarLEDs/Controllers/FireFlyW/WiFi/wifi.h"
#include "../config.h"

extern HAIntegration haIntegration;

void ha_core1_entry();

void HAIntegration::configure() {

}

void HAIntegration::connect() {
	if( WIFI_ENABLE ) {
		wifi_init();
	}
}

void HAIntegration::switchHandler(bool state, HASwitch* sender) {

}

void HAIntegration::loop() {
	printf("Welcome to the real world!\n");
}

void ha_core1_entry() {
	sleep_ms(10); // so that the dma channel doesn't get claimed
	haIntegration.connect();
	multicore_lockout_victim_init();
	haIntegration.configure();

	while(1) {
		haIntegration.loop();
	}
}

HAIntegration::HAIntegration() {
	multicore_launch_core1(ha_core1_entry);
}