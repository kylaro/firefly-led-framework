#include "HAIntegration.h"
#include "pico/time.h"
#include "pico/multicore.h"
#include "../../FireFlyW/WiFi/wifi.h"
#include "../../../../config.h"
#include "ha_mqtt.h"


void ha_core1_entry();

void HAIntegration::loop() {
	
}

void HAIntegration::configure() {
	
}

void HAIntegration::connect() {
	
}

bool HAIntegration::getEnabled() {
	return get_ha_data()->enabled;
}

void ha_core1_entry() {
	sleep_ms(10); // so that the dma channel doesn't get claimed
	wifi_init();

	multicore_lockout_victim_init();

	ha_mqtt_init();
	ha_mqtt_loop();
	
	cyw43_arch_deinit();
}

HAIntegration::HAIntegration() {
	multicore_launch_core1(ha_core1_entry);
}