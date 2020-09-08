#include "uart.h"
#ifndef GPIO_H
#define GPIO_H

enum
{
    GPIO_BASE    = 0x3F200000,           // GPIO Base Address
    GPFSEL0      = (GPIO_BASE + 0x00),
    GPFSEL1      = (GPIO_BASE + 0x04),   
    GPPUD        = (GPIO_BASE + 0x94),   // GPIO Pin Pull Up/Down Enable
    GPPUDCLK0    = (GPIO_BASE + 0x98),   // GPIO Pin Pull Up/Down Enable Clock 0
};


void gpio_enable();

#endif