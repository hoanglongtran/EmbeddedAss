#include "i2c.h"

// Initialize i2c
void i2c_init()
{
    i2c_control_t control;
    bzero(&control, 4);
    // Enable I2C from Control register
    control.i2c_enabled = 1;
    mmio_write(I2C_CONTROL, control.as_int);
    delay(150);
    //Enable GPIO clock for GPIO2 and GPIO3
    mmio_write(GPPUDCLK0, (1 << 2) | (1 << 3));
    delay(150);
    mmio_write(0x3F200000, 0b100 << 6 | 0b100 << 9);
    mmio_write(GPPUDCLK0, 0x00000000);
    do
    {
        control = read_control();
    } while (!control.i2c_enabled);
    putc('n'); // For debugging purpose
}

// Read the status from the Status register
i2c_status_t read_status(void)
{
    i2c_status_t status;
    status.as_int = mmio_read(I2C_STATUS);
    return status;
}

// Read the controller data from Controller register
i2c_control_t read_control(void)
{
    i2c_control_t control;
    control.as_int = mmio_read(I2C_CONTROL);
    return control;
}

// Start i2c transfer
void i2c_start()
{
    i2c_control_t control;
    i2c_status_t status;
    control = read_control(); 
    control.start_transfer = 1;
    mmio_write(I2C_CONTROL, control.as_int);
    //Hold the program until transfer is activated
    do
    {
        status = read_status();
    } while (!status.transfer_active);
}

// Set Read/Write 0: Write, 1: Read
void set_read_write(uint8_t action) 
{
    i2c_control_t control;
    control = read_control();
    control.i2c_read = action;
    mmio_write(I2C_CONTROL, control.as_int);
    if (action == 1) // If READ
    {
        do
        {
            control = read_control();
        } while (!control.i2c_read);
    }else if (action == 0) // If WRITE
    {
        do
        {
            control = read_control();
        } while (control.i2c_read);
    }
}

// Clear FIFO register
void clear_fifo()
{
    i2c_control_t control;
    i2c_status_t status;
    control = read_control();
    control.clear = 1;
    mmio_write(I2C_CONTROL, control.as_int);
    // Wait until FIFO is cleared
    do
    {
        status = read_status();
    } while (status.rxd_contains_data);
}

// Clear Status register
void clear_status()
{
    i2c_status_t status; 
    status = read_status();
    status.transfer_done = 1;
    status.clkt_time_out = 1;
    status.error = 1;
    mmio_write(I2C_STATUS, status.as_int);
    // Wait until register is cleared
    do
    {
        status = read_status();
    } while (status.error || status.clkt_time_out || status.transfer_done);
}

// Set data length needed into DLEN register
void set_data_length(uint32_t length)
{
    mmio_write(I2C_DLEN, length);
}

// Set slave address into Address register
void i2c_address(uint32_t address)
{
    i2c_status_t status;
    mmio_write(I2C_ADDRESS, address);
    do
    {
        status = read_status();
    } while (status.error);
    putc('a'); // For debugging purpose
}

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
            buff[i] = i2c_get();
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
void print_time(uint32_t buff[])
{
    // Day
    switch (buff[3])
    {
        case 1: 
            puts("Monday");
            break;
        case 2:
            puts("Tuesday"); 
            break;
        case 3: 
            puts("Wednesday");
            break;
        case 4: 
            puts("Thursday");
            break;
        case 5: 
            puts("Friday");
            break;
        case 6: 
            puts("Saturday");
            break;
        case 7: 
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
    puts(convert_time(buff[2]));
    putc(':');
    // Minutes
    puts(convert_time(buff[1]));
    putc(':');
    // Seconds
    puts(convert_time(buff[0]));
    putc('\n');
}

// Binary-coded decimal, first digit is represented by 4 bits (0-9), second digit is represented by the last 3 bits (0-5)
uint8_t bcd_to_dec(uint32_t binary_second)
{
    // Dividing a binary to 16 (1 0000 in base 2) basically means right shifting the bit by 4
    // https://stackoverflow.com/questions/1408361/unsigned-integer-to-bcd-conversion
	return ((binary_second/16 * 10) + (binary_second % 16));
}

// Get data from FIFO
uint32_t i2c_get()
{
    i2c_status_t status;
    do
    {
        status = read_status();
        
    } while (status.txe_empty); // Wait for the flag register to announce if the queue is empty or full
    return mmio_read(I2C_FIFO);

}

// Put data into FIFO
void i2c_put(uint32_t data)
{
    i2c_status_t status;
    mmio_write(I2C_FIFO, data);
    // Wait until it's done
    do
    {
        status = read_status();
    } while (!status.txe_empty);
}

// Set time function, used to init time for the RTC for the first time, need to enable I2C and provide RTC address first
void set_time()
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
    i2c_put(0x00000000);
    // Minute
    i2c_put(0b00111001);
    // Hour
    i2c_put(0b00010110);
    // Day
    i2c_put(0b00000001);
    // Date
    i2c_put(0b00010010);
    // Month
    i2c_put(0b00001000);
    // Year
    i2c_put(0b00011001);
    // Wait until transfer is done
    do
    {
        status = read_status();
    } while (!status.transfer_done);
    //putc('d'); // For debugging purpose
}