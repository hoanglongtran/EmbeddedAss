#include "i2c.h"
#include "uart.h"
#ifndef KERNEL_H
#define KERNEL_H

void kernel_main();

char getc(void); 

void putc(char c); 

void gets(char* buf, int buflen); 
    
void puts(const char* buf);

void i2c_address(uint32_t address);

void set_read_write(uint8_t action);

void set_data_length(uint32_t length);

void i2c_start();

void i2c_init();

void i2c_put(uint32_t data);

uint32_t i2c_get();

void i2c_gets(char* buf, int buflen);

void clear_status();

void clear_fifo();

void print_time(uint32_t buff[]);

void get_time(uint32_t * buff);

void pause_uart();
#endif