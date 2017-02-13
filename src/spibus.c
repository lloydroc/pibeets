#include <string.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<stdint.h>
#include<linux/spi/spidev.h>
#include "spibus.h"

int
spi_open(const char dev[], int mode, int oflag)
{
    int fd;
    char spidev[80];
    strcpy(spidev,SPIPATH);
    strcat(spidev,dev);
    printf("Opening SPI device %s\n",spidev);
    // The following calls set up the SPI bus properties
    if ((fd = open(spidev, oflag))<0){
        perror("SPI Error: Can't open device.");
        return -1;
    }
    if(oflag == O_WRONLY || oflag == O_RDWR) {
        if (ioctl(fd, SPI_IOC_WR_MODE, &mode)==-1){
            perror("SPI: Can't set SPI write mode.");
            return -1;
        }
    }
    if(oflag == O_RDONLY || oflag == O_RDWR) {
        if (ioctl(fd, SPI_IOC_RD_MODE, &mode)==-1){
            perror("SPI: Can't get SPI read mode.");
            return -1;
        }
    }
    return fd;
}
