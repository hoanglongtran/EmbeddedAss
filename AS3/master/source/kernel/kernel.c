#include "kernel.h"

void kernel_main()
{
    uint32_t time[7] = {0,0,0,0,0,0,0};
    bool mode = false;
    // Setup GPIO pins for SPI, UART and I2C
    gpio_enable();
    // Enable UART
    uart_init();
    // Enable I2C
    i2c_init();
    // Enable SPI
    spi_init();

    char *greeting =    "EEET2490: Embedded Systems - Operating Systems & Interfacing\n"
                        "------------------------------------------------------------\n"
                        "Assessment Group: 8\n"
                        "s3698200: Do Bao Ngoc\n"
                        "s3373237: Le Minh Quang\n"
                        "s3635165: Tran Hoang Long\n\n"

                        "DS1307 Real Time Clock Data\n"
                        "---------------------------\n";
    puts(greeting);
    
    // Set Address
    i2c_address(0x68);

    // Clear I2C FIFO
    clear_fifo();

    // Clear Status
    clear_status();

    // Clear SPI FIFO
    spi_clear_fifo();
    
    // Set time function, used once to init time to the RTC
    // The order is second, minute, hour, day, date, month, year
    //set_time(0x50, 0x59, 0x12, 0x14, 0x02, 0x08, 0x19 );

    // Loop infinitely
    while (1)
    {   
        // Pause UART when pressing 'p' or 'P', resume when press 'r' or 'R'
        // If 'r' or 'R' is pressed, switch between 12-hour mode and 24-hour mode
        mode = uart_controler(mode);
        
        trasfer_data(time, mode);

        // Set delay
        delay(5006000);
    }
    
}


