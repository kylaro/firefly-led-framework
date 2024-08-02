#include <stdio.h>
#include <string.h>
#include "flash.h"
#include "hardware/flash.h"
#include "hardware/sync.h"

// Storage locations in flash memory
#define FLASH_TARGET_OFFSET (256 * 1024)

// Default device information
#define DEFAULT_DEVICE_NAME "Firefly"
#define DEFAULT_ENTITY_NAME "Board LED"
#define DEFAULT_DEVICE_MODEL "Pico W"
#define DEFAULT_DEVICE_MANUFACTURER "Raspberry"

device_info_t device_info;

// Function to save device information to flash memory
void flash_write_device_info() {
    uint8_t flash_data[FLASH_SECTOR_SIZE];
    memset(flash_data, 0xFF, FLASH_SECTOR_SIZE);
    memcpy(flash_data, &device_info, sizeof(device_info_t));

    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
    flash_range_program(FLASH_TARGET_OFFSET, flash_data, FLASH_SECTOR_SIZE);
    restore_interrupts(ints);
}

// Function to read device information from flash memory
void flash_read_device_info() {
    const uint8_t *flash_data = (const uint8_t *)(XIP_BASE + FLASH_TARGET_OFFSET);
    memcpy(&device_info, flash_data, sizeof(device_info_t));

    // If the flash data is invalid, use default values
    if (strlen(device_info.name) == 0 || strlen(device_info.model) == 0) {
        snprintf(device_info.name, sizeof(device_info.name), DEFAULT_DEVICE_NAME);
        snprintf(device_info.entity, sizeof(device_info.entity), DEFAULT_ENTITY_NAME);
    }
}

