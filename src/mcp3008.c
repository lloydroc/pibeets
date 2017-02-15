#include "mcp3008.h"

int
transfer(int fd, unsigned char send[], unsigned char rec[], int len);

int
read_mcp3008(int fd, const unsigned char channels[], int sampl[], int n_sampl, int diff_pair) {
    int i; // loop index
    // The send buffer to grab each sample is 24-bit
    int len = n_sampl*3;
    int ret; // return code
    unsigned char *send,*rec;
    rec  = (unsigned char *) malloc(len);
    send = (unsigned char *) malloc(len);

    // Only way to understand this code is to consult the
    // MCP3008 Datasheet on the timing diagram to a microcontroller
    for(i=0;i<n_sampl;i++) {
        send[3*i+0] = 0b00000001; // Start bit for each transfer
        send[3*i+1] = channels[i];    // Channel we're sending to
        send[3*i+1] <<= 4;        // Shift up to align
        if(diff_pair == 0) send[3*i+1] |= 0b10000000;
    }

    // Tranfer data in/out of the SPI bus
    ret = transfer(fd,send,rec,len);

    // format the data back into 10-bit values
    for(i=0;i<n_sampl;i++) {
       sampl[i] = (rec[3*i+1]<<8)|rec[3*i+2];
       // TODO subtract 512 to center @ 0
    }

    free(send);
    free(rec);

    return ret;
}

// Transfer data in and out of the SPI bus
// Inspired by Derek Molloy in his
// Exploring Raspberry Pi Book
// http://exploringrpi.com/chapter8/
int
transfer(int fd, unsigned char send[], unsigned char rec[], int len)
{
    struct spi_ioc_transfer transfer;          // the transfer structure
    transfer.tx_buf = (unsigned long) send;    // the buffer for sending data
    transfer.rx_buf = (unsigned long) rec;     // the buffer for receiving data
    transfer.len = len;                        // the length of buffer
    transfer.speed_hz = SPI_TRANSFER_SPEED_HZ; // max speed is 1.35MHz, but it won't work
    transfer.bits_per_word = 8;                // bits per word
    transfer.delay_usecs = 0;                  // delay in us
    transfer.cs_change = 0;                    // affects chip select after transfer
    transfer.tx_nbits = 0;                     // no. bits for writing (default 0)
    transfer.rx_nbits = 0;                     // no. bits for reading (default 0)
    transfer.pad = 0;                          // interbyte delay - check version

    // send the SPI message (all of the above fields, inc. buffers)
    // 1 is the number of spi_ioc_transfer structs to send
    int status = ioctl(fd, SPI_IOC_MESSAGE(1), &transfer);
    if (status < 0) {
        perror("SPI: SPI_IOC_MESSAGE Failed");
        return -1;
    }
    return status;
}
