#include "gpio.h"

void gpio_enable(){
    // Disable pull-up/pull-down register
    mmio_write(GPPUD, 0x00000000);
    delay(150);
    // Set CLK signal for pin 2, pin 3, pin 9, pin 10, pin 11, pin 14
    mmio_write(GPPUDCLK0, (1 << 2) | (1 << 3) | (1 << 9) | (1 << 10) | (1 << 11) | (1 << 14) | (1 << 15));
    delay(150);    
    mmio_write(GPPUDCLK0, 0x00000000);
    // Enable alternate function for pin 2, pin 3, pin 8, pin 9
    mmio_write(GPFSEL0, (0b100 << 6) | (0b100 << 9) | (0b100 << 24) | (0b100 << 27));
    // Enable alternate function for pin 10, pin 11, pin 14, pin 15
    mmio_write(GPFSEL1, (0b100 << 00) | (0b100 << 3) | (0b100 << 12) | (0b100 << 15));
}