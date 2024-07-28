#ifndef FLASH_H
#define FLASH_H

typedef struct {
    char name[32];
    char entity[32];
    char model[32];
    char manufacturer[32];
} device_info_t;

void flash_read_device_info();
void flash_write_device_info();

#endif // FLASH_H