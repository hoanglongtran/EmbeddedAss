#include "rtc.h"

// Get the time data from FIFO
void get_time(uint32_t * buff)
{
    uint32_t i = 0;
    i2c_status_t status;
    status = read_status();
    while (!(status.transfer_done))
    {
        while (status.rxd_contains_data)
        {           
            buff[i] = spi_transfer(i2c_get());;
            i++;               
            status = read_status(); 
        }
        status = read_status();
    }
}

// Convert time into char, add '0' if time only has one digit
char* convert_time(uint32_t second_binary)
{
    uint8_t second = bcd_to_dec(second_binary);
    char* second_char = itoa(second);
    if (second < 10)
    {
        putc('0');
    }
    return second_char;
}

// Print formatted time into UART console
void print_time(uint32_t buff[], bool mode)
{
    // Day
    switch (buff[3])
    {
        case MONDAY: 
            puts("Monday");
            break;
        case TUESDAY:
            puts("Tuesday"); 
            break;
        case WEDNESDAY: 
            puts("Wednesday");
            break;
        case THURSDAY: 
            puts("Thursday");
            break;
        case FRIDAY: 
            puts("Friday");
            break;
        case SATURDAY: 
            puts("Saturday");
            break;
        case SUNDAY: 
            puts("Sunday");
            break;
        default: 
            break;
    }
    putc(' ');
    // Date
    puts(convert_time(buff[4]));
    putc('/');
    // Month
    puts(convert_time(buff[5]));
    putc('/');
    // Year
    puts(convert_time(buff[6]));
    putc(' ');
    // Hours
    // If mode is true and the current hour is > 12
    if (mode && buff[2] > 0x12)
        puts(convert_time(buff[2]- 0x12));
    else
        puts(convert_time(buff[2]));
    putc(':');
    // Minutes
    puts(convert_time(buff[1]));
    putc(':');
    // Seconds
    puts(convert_time(buff[0]));
    // From 12:00 - 23:59 : PM
    if (mode && buff[2] >= 0x12)
        puts(" PM");
    // From 0:00 - 11:59 : AM
    else if (mode && buff[2] < 0x12)
        puts(" AM");
    putc('\n');
}

// Binary-coded decimal, first digit is represented by 4 bits (0-9), second digit is represented by the last 3 bits (0-5)
uint8_t bcd_to_dec(uint32_t binary_second)
{
    // Dividing a binary to 16 (1 0000 in base 2) basically means right shifting the bit by 4
    // https://stackoverflow.com/questions/1408361/unsigned-integer-to-bcd-conversion
	return ((binary_second/16 * 10) + (binary_second % 16));
}

// Set time function, used to init time for the RTC for the first time, need to enable I2C and provide RTC address first
// Improved to allow directly set the time using hex number
void set_time(uint32_t second, uint32_t minute, uint32_t hour, uint32_t day, uint32_t date, uint32_t month, uint32_t year)
{
    i2c_status_t status;
    // Set data length
    set_data_length(0x08);
    // Set Write
    set_read_write(0);
    // Start transfer
    i2c_start();   
    // Register address
    i2c_put(0x00000000);
    // Second
    i2c_put(second);
    // Minute
    i2c_put(minute);
    // Hour
    i2c_put(hour);
    // Day
    i2c_put(day);
    // Date
    i2c_put(date);
    // Month
    i2c_put(month);
    // Year
    i2c_put(year);
    // Wait until transfer is done
    do
    {
        status = read_status();
    } while (!status.transfer_done);
    //putc('d'); // For debugging purpose
}

// Full sequence of reading data from RTC via I2C, send it out to MOSI, receive the data back from MISO, convert and format the data
// then print the data out into UART
void trasfer_data(uint32_t * buff, bool mode)
{
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
    get_time(buff);

    // Print the clock data to UART Debugger
    print_time(buff, mode);
}