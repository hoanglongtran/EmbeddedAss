#include "uart.h"

void mmio_write(uint32_t reg, uint32_t data)
{
    *(volatile uint32_t*)reg = data;
}

uint32_t mmio_read(uint32_t reg)
{
    return *(volatile uint32_t*)reg;
}

uint32_t bcm2835_peri_read_nb(volatile uint32_t* paddr)
{
	return *paddr;
}

uart_flags_t read_flags(void)
{
    uart_flags_t flags;
    flags.as_int = mmio_read(UART0_FR); //Read the flag register, then save into the Flag union as int, can be accessed bit by bit via the 
                                        //struct inside the union
    return flags;
}

unsigned char uart_getc(void)
{
    uart_flags_t flags;
    do
    {
        flags = read_flags();
    } while (flags.receive_queue_empty); // Wait for the flag register to announce if the queue is empty or full
    return mmio_read(UART0_DR);
}

void uart_putc(unsigned char c)
{
    uart_flags_t flags;
    do
    {
        flags = read_flags();
    } while (flags.transmit_queue_full);
    mmio_write(UART0_DR, c);
}

void uart_init(void)
{
    uart_control_t control;
    bzero(&control, 4); 
    mmio_write(UART0_CR, control.as_int);
    mmio_write(GPPUD, 0x00000000);
    delay(150);    
    mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);    
    mmio_write(GPPUDCLK0, 0x00000000);
    mmio_write(UART0_ICR, 0x7FF);
    mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));
    mmio_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
                           (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));
    control.uart_enabled = 1;
    control.transmit_enabled = 1;
    control.receive_enabled = 1;
    mmio_write(UART0_CR, control.as_int);
}
// Pause the UART output when user presses 'p' or 'P', resume when user presses 'r' or 'R'
void pause_uart()
{
    char c = mmio_read(UART0_DR);
    // Convert uppercase letter into lowercase
    if ((c >= 65) && (c <= 90))
        c = c + 32; 
    // If user presses 'p' or 'P', enter loop, holding the UART output 
    if (c == 'p')
    {
        do
        {
            c = mmio_read(UART0_DR);
            // Convert uppercase letter into lowercase
            if ((c >= 65) && (c <= 90))
                c = c + 32;
        } while (c != 'r'); // Exit when user presses 'r' or 'R'
    }
}