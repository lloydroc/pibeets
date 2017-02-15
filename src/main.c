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

void print_timetaken(char label[], struct timeval start, struct timeval end) {
    double usec,sec;
    usec = (double) (end.tv_usec - start.tv_usec)/1000000;
    sec  = (double) (end.tv_sec - start.tv_sec);
    printf("%s: Time Taken = %f",label,sec+usec);
}

int
main()
{
    int i; // loop index
    struct timeval t1,t2; // to time our function calls
    // We will read 2 samples from the MCP3008 on channels 1 and 0
    // Read in singled ended mode
    unsigned char channels[2];
    channels[0] = 0;
    channels[1] = 1;
    int sampl[2]; // where the 2 10-bit samples will go

    int fd_gpio4 = gpio_setup_output(4);
    gpio_write(fd_gpio4,0); // Set low to start with

    // We will use /dev/spidev0.0 with spi mode 3
    int fd_spi0 = spi_open("0.0",3,O_RDWR);
    gettimeofday(&t1,NULL);
    gpio_write(fd_gpio4,1); // Set hi for SPI portion
    if(read_mcp3008(fd_spi0,channels,sampl,2,0)!=0) {
        perror("Failed to transfer bytes");
        return EXIT_FAILURE;
    }
    gpio_write(fd_gpio4,0);
    gettimeofday(&t2,NULL);

    print_timetaken("Read 2 Samples",t1,t2);

    // Print the data
    for(i=0; i<1; i++) {
        printf("Channel[%d]: %d\n",i,sampl[i]);
    }
    gpio_close(fd_gpio4,4);
    close(fd_spi0);               // close the file
    return EXIT_SUCCESS;
}
