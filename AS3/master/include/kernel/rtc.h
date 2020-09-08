#include "gpio.h"
#include "i2c.h"
#include "spi.h"
#ifndef RTC_H
#define RTC_H

enum
{
    MONDAY = 1,
    TUESDAY = 2,
    WEDNESDAY = 3,
    THURSDAY = 4,
    FRIDAY = 5,
    SATURDAY = 6,
    SUNDAY = 7,
};

void print_time(uint32_t buff[], bool mode);

void get_time(uint32_t * buff);

void set_time(uint32_t second, uint32_t minute, uint32_t hour, uint32_t day, uint32_t date, uint32_t month, uint32_t year);

void trasfer_data(uint32_t * buff, bool mode);

char* convert_time(uint32_t second_binary);

uint8_t bcd_to_dec(uint32_t binary_second);

uint32_t spi_transfer(uint32_t data);

#endif