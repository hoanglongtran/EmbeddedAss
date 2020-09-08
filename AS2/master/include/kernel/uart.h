#include "stddef.h"
#include "stdint.h"
#include "stdlib.h"
#ifndef UART_H
#define UART_H


enum
{
    GPIO_BASE    = 0x3F200000,           // GPIO Base Address
    GPPUD        = (GPIO_BASE + 0x94),   // GPIO Pin Pull Up/Down Enable
    GPPUDCLK0    = (GPIO_BASE + 0x98),   // GPIO Pin Pull Up/Down Enable Clock 0
    UART0_BASE   = (GPIO_BASE + 0x1000), // UART Base Address
    UART0_DR     = (UART0_BASE + 0x00),  // Data Register
    UART0_RSRECR = (UART0_BASE + 0x04),  // Receive Status Register / Error Clear Register
    UART0_FR     = (UART0_BASE + 0x18),  // Flag Register
    UART0_ILPR   = (UART0_BASE + 0x20),  // Disable IrDA Register
    UART0_IBRD   = (UART0_BASE + 0x24),  // Integer Baud Rate Division Register
    UART0_FBRD   = (UART0_BASE + 0x28),  // Fractional Baud Rate Division Register
    UART0_LCRH   = (UART0_BASE + 0x2C),  // Line Control Register
    UART0_CR     = (UART0_BASE + 0x30),  // Control Register
    UART0_IFLS   = (UART0_BASE + 0x34),  // Interrupt FIFO Level Select Register
    UART0_IMSC   = (UART0_BASE + 0x38),  // Interrupt Mask Set / Clear Register
    UART0_RIS    = (UART0_BASE + 0x3C),  // Raw Interrupt Status Register
    UART0_MIS    = (UART0_BASE + 0x40),  // Masked Interrupt Status Register
    UART0_ICR    = (UART0_BASE + 0x44),  // Interrupt Clear Register
    UART0_DMACR  = (UART0_BASE + 0x48),  // Disable DMA Control Register
    UART0_ITCR   = (UART0_BASE + 0x80),  // Test Control Register
    UART0_ITIP   = (UART0_BASE + 0x84),  // Test Control Register
    UART0_ITOP   = (UART0_BASE + 0x88),  // Test Control Register
    UART0_TDR    = (UART0_BASE + 0x8C),  // Test Data Register
};

typedef union uart_flags
{
    struct
    {
        uint8_t clear_to_send : 1;
        uint8_t data_set_ready : 1;
        uint8_t data_carrier_detected : 1;
        uint8_t busy : 1;
        uint8_t receive_queue_empty : 1;
        uint8_t transmit_queue_full : 1;
        uint8_t receive_queue_full : 1;
        uint8_t transmit_queue_empty : 1;
        uint8_t ring_indicator : 1;
        uint32_t padding : 23;
    };
    uint32_t as_int;
} uart_flags_t;

typedef union uart_control
{
    struct
    {
        uint8_t uart_enabled : 1;
        uint8_t sir_enabled : 1;
        uint8_t sir_low_power_mode : 1;
        uint8_t reserved : 4;
        uint8_t loop_back_enabled : 1;
        uint8_t transmit_enabled : 1;
        uint8_t receive_enabled : 1;
        uint8_t data_transmit_ready : 1;
        uint8_t request_to_send : 1;
        uint8_t out1 : 1;
        uint8_t out2 : 1;
        uint8_t rts_hardware_flow_control_enabled : 1;
        uint8_t cts_hardware_flow_control_enabled : 1;
        uint16_t padding;
    };
    uint32_t as_int;
} uart_control_t;



void mmio_write(uint32_t reg, uint32_t data);

uint32_t mmio_read(uint32_t reg);

uart_flags_t read_flags(void);

unsigned char uart_getc(void);

void uart_putc(unsigned char c);

void uart_init(void);

uint32_t bcm2835_peri_read_nb(volatile uint32_t* paddr);

void pause_uart();

#endif