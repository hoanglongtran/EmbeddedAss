#include "stddef.h"
#include "stdint.h"
#include "stdlib.h"
#include "stdio.h"
#include "uart.h"
#ifndef SPI_H
#define SPI_H
enum
{
    SPI_BASE            = 0x3F204000,           // I2C Base Address
    SPI_CONTROL_STATUS  = (SPI_BASE + 0x00),    // I2C Control & Status Register
    SPI_FIFO            = (SPI_BASE + 0x04),    // Data FIFO Register
    SPI_CLK             = (SPI_BASE + 0x08),    // Data Delay Register  
    SPI_DLEN            = (SPI_BASE + 0xC),    // Data Length Register
};

typedef union spi_cs
{
    struct
    {
        uint8_t chip_select : 2;    // Chip Select
        uint8_t cpha : 1;           // Clock Phase
        uint8_t cpol : 1;           // Clock Polarity
        uint8_t clear : 2;          // CLEAR FIFO Clear
        uint8_t cspol : 1;          // Chip Select Polarity
        uint8_t ta : 1;             // Transfer Active
        uint8_t dmaen :1;           // DMAEN DMA Enable - Unused
        uint8_t intd :1;            // INTD Interrupt on Done
        uint8_t intr : 1;           // INTR Interrupt on RXR
        uint8_t adcs : 1;           // ADCS Automatically Deassert Chip Select - Unused
        uint8_t ren: 1;             // REN Read Enable
        uint8_t len: 1;             // LEN LoSSI enable - Unused
        uint8_t lmono_te_en: 2;     // Unused
        uint8_t done: 1;            // Done transfer Done
        uint8_t rxd: 1;             // RXD RX FIFO contains Data
        uint8_t txd: 1;             // TXD TX FIFO can accept Data
        uint8_t rxr: 1;             // RXR RX FIFO needs Reading ( full)
        uint8_t rxf: 1;             // RXF - RX FIFO Ful
        uint8_t cspol0: 1;          // Chip Select 0 Polarity
        uint8_t cspol1: 1;          // Chip Select 1 Polarity
        uint8_t cspol2: 1;          // Chip Select 2 Polarity
        uint8_t padding;
    };
    uint32_t as_int;
}spi_cs_t;

void spi_init();

spi_cs_t read_cs(void);

void spi_clear_fifo();

uint32_t spi_get();

void spi_put(uint32_t data);

uint32_t spi_transfer(uint32_t data);
#endif