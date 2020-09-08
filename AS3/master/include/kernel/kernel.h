#include "i2c.h"
#include "uart.h"
#include "spi.h"
#include "gpio.h"
#include "rtc.h"
#include "stdbool.h"
#ifndef KERNEL_H
#define KERNEL_H

void kernel_main();

void gpio_enable();

void uart_init(void);

void i2c_init();

void spi_init();
    
void puts(const char* buf);

void i2c_address(uint32_t address);

void clear_fifo();

void clear_status();

void spi_clear_fifo();

void trasfer_data(uint32_t * buff, bool mode);

void delay(uint32_t count);

#endif