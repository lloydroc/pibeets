#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<stdint.h>
#include<linux/spi/spidev.h>
#include "spibus.h"

// Inspired by Derek Molloy in his
// Exploring Raspberry Pi Book
// http://exploringrpi.com/chapter8/


int
transfer(int fd, unsigned char send[], unsigned char rec[], int len)
{
    struct spi_ioc_transfer transfer;        // the transfer structure
    transfer.tx_buf = (unsigned long) send;  // the buffer for sending data
    transfer.rx_buf = (unsigned long) rec;   // the buffer for receiving data
    transfer.len = len;                      // the length of buffer
    transfer.speed_hz = 135000;              // max speed is 1.35MHz, but it won't work
    transfer.bits_per_word = 8;              // bits per word
    transfer.delay_usecs = 0;                // delay in us
    transfer.cs_change = 0;                  // affects chip select after transfer
    transfer.tx_nbits = 0;                   // no. bits for writing (default 0)
    transfer.rx_nbits = 0;                   // no. bits for reading (default 0)
    transfer.pad = 0;                        // interbyte delay - check version

    // send the SPI message (all of the above fields, inc. buffers)
    // 1 is the number of spi_ioc_transfer structs to send
    int status = ioctl(fd, SPI_IOC_MESSAGE(1), &transfer);
    if (status < 0) {
        perror("SPI: SPI_IOC_MESSAGE Failed");
        return -1;
    }
    return status;
}

int
main()
{
   int i;                              // file handle and loop counter

   int fd = spi_open("0.0",3,O_RDWR);

   for (i=0; i<1; i++)
   {
      unsigned char send[3], receive[3];
      send[0] = 0b00000001;     // Set start bit high
      send[1] = 0b10000000;     // Set Single ended for channel 0
      send[2] = 0; // not relevant but makes scope look clean

      // This function can send and receive data, just sending now
      if (transfer(fd, send, receive, 3)==-1){
         perror("Failed to transfer bytes");
         return -1;
      }
      receive[1] &= 0b00000011; // We only get 10-bits mask off the 6
      int val = (receive[1]<<8)|receive[2];
      printf("Data Received: %d\n", val);
      fflush(stdout);       // need to flush the output, no \n
      usleep(500000);       // sleep for 500ms each loop
   }
   close(fd);               // close the file
   return 0;
}
