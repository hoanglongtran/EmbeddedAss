#include "kernel.h"

void kernel_main()
{
    uint32_t time[7] = {0,0,0,0,0,0,0};
    // Init UART interface
    uart_init();

    char *greeting =    "EEET2490: Embedded Systems - Operating Systems & Interfacing\n"
                        "------------------------------------------------------------\n"
                        "Assessment Group: 8\n"
                        "s3698200: Do Bao Ngoc\n"
                        "s3373237: Le Minh Quang\n"
                        "s3635165: Tran Hoang Long\n\n"

                        "DS1307 Real Time Clock Data\n"
                        "---------------------------\n";
    puts(greeting);

    // Enable I2C
    i2c_init();

    // Set Address
    i2c_address(0x68);

    // Clear FIFO
    clear_fifo();

    // Clear Status
    clear_status();
    
    // Set time function, used once to init time to the RTC
    //set_time();

    // Loop infinitely
    while (1)
    {   
        // Pause UART when pressing 'p' or 'P', resume when press 'r' or 'R'
        pause_uart();
        // Clear FIFO
        clear_fifo();

        // Clear Status
        clear_status();

        // Set data length
        set_data_length(0x01);

        // Set Write
        set_read_write(0);

        // Start transfer
        i2c_start();

        // Set register address
        i2c_put(0x00000000); 

        // Clear FIFO, preparing for reading RTC data
        clear_fifo();

        // Clear Status
        clear_status();

        // Get 7 bytes from RTC, containing Day, Date, Month, Year, Hour, Minute, Second
        set_data_length(0x07);

        //Set Read
        set_read_write(1);

        //Send repeated start
        i2c_start();

        // Get clock data from RTC, passing time array address to the function to modify directly
        get_time(time);

        // Print the clock data to UART Debugger
        print_time(time);

        // Set delay
        delay(5005000);
    }
    
}


