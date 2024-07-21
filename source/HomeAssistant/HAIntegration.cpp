#include "HAIntegration.h"
#include "pico/time.h"
#include "pico/multicore.h"
#include "../kylarLEDs/Controllers/FireFlyW/WiFi/wifi.h"
#include "../config.h"
#include "ha_mqtt.h"

extern HAIntegration haIntegration;

void ha_core1_entry();

void HAIntegration::loop() {
	ha_mqtt_loop();
}

void HAIntegration::configure() {
	if( MQTT_ENABLE ) {
		ha_mqtt_init();
	}
}

void HAIntegration::connect() {
	if( WIFI_ENABLE ) {
		wifi_init();
	}
}

void ha_core1_entry() {
	sleep_ms(10); // so that the dma channel doesn't get claimed
	haIntegration.connect();
	multicore_lockout_victim_init();
	haIntegration.configure();
	haIntegration.loop();
	cyw43_arch_deinit();
}

HAIntegration::HAIntegration() {
	multicore_launch_core1(ha_core1_entry);
}