// scd41.h

#ifndef SCD41_H
#define SCD41_H

#include "pico/stdlib.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initializes the SCD41 sensor for periodic measurements.
 */
void scd41_init(void);

/**
 * @brief Reads CO2, temperature, and humidity values from the SCD41 sensor.
 *
 * @param co2 Pointer to store the CO2 value.
 * @param temp Pointer to store the temperature value.
 * @param humidity Pointer to store the humidity value.
 * 
 * @return True if data was successfully read, false otherwise.
 */
bool scd41_read_data(uint16_t *co2, uint16_t *temp, uint16_t *humidity);

#ifdef __cplusplus
}
#endif

#endif // SCD41_H