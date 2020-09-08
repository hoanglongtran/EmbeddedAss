#include "stddef.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "uart.h"
#ifndef I2C_H
#define I2C_H
enum
{
    
    I2C_BASE    = 0x3F804000,           // I2C Base Address
    I2C_CONTROL = (I2C_BASE + 0x00),    // I2C Control Register
    I2C_STATUS  = (I2C_BASE + 0x04),    // Status Register
    I2C_DLEN    = (I2C_BASE + 0x08),    // Data Length Register
    I2C_ADDRESS = (I2C_BASE + 0xC),     // Slave Address Register
    I2C_FIFO    = (I2C_BASE + 0x10),    // Data FIFO Register
    I2C_DIV     = (I2C_BASE + 0x14),    // Clock Divider Register
    I2C_DEL     = (I2C_BASE + 0x18),    // Data Delay Register
    I2C_CLKT    = (I2C_BASE + 0x1C),    // Clock Stretch Timeout Register
    GPIO_ALT0  = 0b100,                 // Alternate function 0
    
};

typedef union i2c_status
{
    struct
    {
        uint8_t transfer_active : 1;
        uint8_t transfer_done : 1;
        uint8_t txw_needs_writing : 1;
        uint8_t rxr_needs_reading : 1;
        uint8_t txd_can_accept_data : 1;
        uint8_t rxd_contains_data : 1;
        uint8_t txe_empty :1 ;
        uint8_t rxf_full :1 ;
        uint8_t error : 1;
        uint8_t clkt_time_out : 1;
        uint16_t padding;
    };
    uint32_t as_int;
}i2c_status_t;

typedef union i2c_control
{
    struct 
    {
        uint8_t i2c_read : 1;
        uint8_t reserved : 3;
        uint8_t clear : 2;
        uint8_t another_reserved : 1;
        uint8_t start_transfer : 1;
        uint8_t interrupt_on_done : 1;
        uint8_t interrupt_on_tx :1 ;
        uint8_t interrupt_on_rx :1 ;
        uint8_t another_another_reserved : 4;
        uint8_t i2c_enabled : 1;
        uint16_t padding;
    };
    uint32_t as_int;
}i2c_control_t;

void i2c_init();

void i2c_start();

void set_read_write(uint8_t action);

void set_data_length(uint32_t length);

void i2c_address(uint32_t address);

void clear_status();

void clear_fifo();

i2c_status_t read_status(void);

uint32_t i2c_get();

void i2c_put(uint32_t data);

i2c_control_t read_control(void);

char* convert_time(uint32_t second_binary);

char* convert_minute(uint32_t minute_binary);

uint8_t bcd_to_dec(uint32_t binary_second);

void print_time(uint32_t buff[]);

void get_time(uint32_t * buff);

void set_time();
#endif