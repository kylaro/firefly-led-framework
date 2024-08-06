#ifndef FLASH_H
#define FLASH_H

#include <stdint.h>

#define MAX_NAME_LENGTH (32U)
#define FLASH_BASE      (0x0)
#define DATA_MARKER     (0xA5)
// Storage locations in flash memory
#define FLASH_TARGET_OFFSET (256 * 1024)
// Default device information
#define DEFAULT_DEVICE_NAME "Firefly"
#define DEFAULT_ENTITY_NAME "Board LED"

typedef struct {
    char name[MAX_NAME_LENGTH];
    char entity[MAX_NAME_LENGTH];
    uint8_t is_valid;
} device_info_t;

void flash_read_device_info();
void flash_write_device_info();

#endif // FLASH_H