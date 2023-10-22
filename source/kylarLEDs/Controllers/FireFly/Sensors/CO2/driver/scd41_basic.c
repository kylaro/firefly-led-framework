#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "stdio.h"

#define SCD41_I2C_ADDRESS      0x62  // Assuming default I2C address for SCD41
#define START_PERIODIC_MEASURE 0x21b1
#define GET_DATA_READY         0xe4b8
#define READ_MEASUREMENT       0xec05

bool scd41_write_command(uint16_t command) {
    uint8_t data[2];
    data[0] = command >> 8;  // MSB
    data[1] = command & 0xFF; // LSB
    int ret = i2c_write_blocking(i2c0, SCD41_I2C_ADDRESS, data, 2, false);
    printf("write command: %d\n", ret);
    return ret == 2;
}

bool scd41_data_ready() {
    uint8_t cmd[2] = { GET_DATA_READY >> 8, GET_DATA_READY & 0xFF };
    uint8_t response[3];
    i2c_write_blocking(i2c0, SCD41_I2C_ADDRESS, cmd, 2, true);
    i2c_read_blocking(i2c0, SCD41_I2C_ADDRESS, response, 3, false);
    return (response[0] & 0x80) != 0;  // Checking the MSB
}

bool scd41_read_data(uint16_t *co2, uint16_t *temp, uint16_t *humidity) {
    //i2c_scan();
    //printf("read data: ");
    if (!scd41_data_ready()){
        //printf("not ready\n");
        return;
    }
    //printf("ok\n");
    uint8_t cmd[2] = { READ_MEASUREMENT >> 8, READ_MEASUREMENT & 0xFF };
    uint8_t response[9];
    i2c_write_blocking(i2c0, SCD41_I2C_ADDRESS, cmd, 2, true);
    i2c_read_blocking(i2c0, SCD41_I2C_ADDRESS, response, 9, false);

    *co2 = (response[0] << 8) | response[1];
    *temp = (response[3] << 8) | response[4];
    *humidity = (response[6] << 8) | response[7];
    return true;
}

void i2c_scan() {
    printf("Scanning I2C bus...\n");
    for (uint8_t addr = 1; addr < 128; addr++) {
        int result = i2c_write_blocking(i2c0, addr, NULL, 0, true);
        if (result != PICO_ERROR_GENERIC) { // If no error, a device is present
            printf("I2C device found at address 0x%x = %d\n", addr, result);
        }
    }
}


void scd41_init() {
    printf("init\n");
    
    stdio_init_all();
    i2c_init(i2c0, 100000);  // Initialize I2C at 40kHz
    gpio_set_function(4, GPIO_FUNC_I2C);  // Assuming SDA is on GP4
    gpio_set_function(5, GPIO_FUNC_I2C);  // Assuming SCL is on GP5
    gpio_pull_up(4);
    gpio_pull_up(5);
    scd41_write_command(START_PERIODIC_MEASURE);
    
}

/*int main() {
    stdio_init_all();
    scd41_init();
    while (true) {
        uint16_t co2, temp, humidity;
        if (scd41_read_data(&co2, &temp, &humidity)) {
            printf("CO2: %d ppm, Temp: %d, Humidity: %d\n", co2, temp, humidity);
        }
        sleep_ms(1000);  // Reading every 1 second. Adjust as needed.
    }
}*/