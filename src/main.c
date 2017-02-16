#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<stdint.h>
#include<ctype.h>
#include<stdlib.h>
#include<stdarg.h>
#include<sys/time.h>
#include<linux/spi/spidev.h>
#include "spibus.h"
#include "mcp3008.h"
#include "gpio.h"
#include "util.h"

#define N_SAMPL 2

int
main()
{
    int i,j; // loop index
    struct timeval t1,t2; // to time our function calls
    // We will read 2 samples from the MCP3008 on channels 1 and 0
    // Read in singled ended mode
    unsigned char channels[N_SAMPL];
    memset(channels,0,N_SAMPL);
    int sampl[N_SAMPL]; // where the 10-bit samples will go

    int fd_gpio4 = gpio_setup_output(4);
    gpio_write(fd_gpio4,0); // Set low to start with

    // We will use /dev/spidev0.0 with spi mode 3
    int fd_spi0 = spi_open("0.0",3,SPI_TRANSFER_SPEED_HZ,O_RDWR);

    for(j=0;j<10;j++) {
        gettimeofday(&t1,NULL);
        gpio_write(fd_gpio4,1); // Set hi for SPI portion
        if(read_mcp3008(fd_spi0,channels,sampl,N_SAMPL,0) == -1) {
            perror("Failed to transfer bytes");
            gpio_close(fd_gpio4,4);
            close(fd_spi0);
            return EXIT_FAILURE;
        }
        gpio_write(fd_gpio4,0);

        //usleep(1000);
        gettimeofday(&t2,NULL);
        print_timetaken("Read Samples",t1,t2);
        // Print the data
        for(i=0; i<1; i++) {
            printf("Channel[%d]: %d\n",i,sampl[i]);
        }
    }

    gpio_close(fd_gpio4,4);
    close(fd_spi0);               // close the file
    return EXIT_SUCCESS;
}
