#ifndef RPI_GPIO_INCLUDE
#define RPI_GPIO_INCLUDE

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

#define GPIO_PATH "/sys/class/gpio/"
#define GPIO_PIN_PATH "/sys/class/gpio/gpio"

// A user-space File I/O GPIO utility
// for the Raspberry Pi
//
// For example to write to gpio4
// int fd = gpio_setup_output(4);
// gpio_write(fd,1);
// gpio_close(fd,4);
// fclose(fd);

// Setup a GPIO Pin
// see pinout.xyz the gpio pin isn't
// the physical pin header but
// numbered from the CPU port
// Before you write or read
// need to setup
// the file descriptor is returned
// to write values to
int
gpio_setup_output(int gpio);

// Write a given binary value to a GPIO pin
// The gpio pin will already have a file
// descriptor from gpio_open
int
gpio_write(int fd, int val);

// After setup we need to close
// the file descriptor
int
gpio_close(int fd, int gpio);

#endif
