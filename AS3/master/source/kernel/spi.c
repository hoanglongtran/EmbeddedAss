#include "spi.h"

void spi_init()
{
    spi_cs_t cs;
    cs = read_cs();
    bzero(&cs, 4);
    cs.ta = 1;
    mmio_write(SPI_CONTROL_STATUS, cs.as_int);
    //putc('p'); // For debugging purpose
}

// Read the status from the Control Status register
spi_cs_t read_cs(void)
{
    spi_cs_t cs;
    cs.as_int = mmio_read(SPI_CONTROL_STATUS);
    return cs;
}

// Clear FIFO register
void spi_clear_fifo()
{
    spi_cs_t cs;
    cs = read_cs();
    cs.clear = 3;
    mmio_write(SPI_CONTROL_STATUS, cs.as_int);
    // Wait until FIFO is cleared
    do
    {
        cs = read_cs();
    } while (cs.rxd);
    //putc('c');
}

// Get data from FIFO
uint32_t spi_get()
{
    spi_cs_t cs;
    do
    {
        cs = read_cs();
        
    } while (!cs.rxd);
    return mmio_read(SPI_FIFO);

}

// Put data into FIFO
void spi_put(uint32_t data)
{
    spi_cs_t cs;
    do
    {
        cs = read_cs();
    } while (!cs.txd);
    mmio_write(SPI_FIFO, data);
    // Wait until it's done

}

uint32_t spi_transfer(uint32_t data){
    uint32_t miso_data;
    spi_cs_t cs;
    spi_clear_fifo();
    spi_init();
    spi_put(data);
    miso_data = spi_get();
    do
    {
        cs = read_cs();
    } while (!cs.done);
    cs.ta = 0;
    mmio_write(SPI_CONTROL_STATUS, cs.as_int);
    return miso_data;
}



