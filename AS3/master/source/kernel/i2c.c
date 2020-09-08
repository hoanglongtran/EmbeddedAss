#include "i2c.h"

// Initialize i2c
void i2c_init()
{
    i2c_control_t control;
    bzero(&control, 4);
    // Enable I2C from Control register
    control.i2c_enabled = 1;
    mmio_write(I2C_CONTROL, control.as_int);
    do
    {
        control = read_control();
    } while (!control.i2c_enabled);
    //putc('n'); // For debugging purpose
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
    //putc('a'); // For debugging purpose
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

