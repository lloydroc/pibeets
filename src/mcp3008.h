#ifndef MCP3008_INCLUDED
#define MCP3008_INCLUDED
#include<stdlib.h>
#include<stdio.h>
#include<sys/ioctl.h>
#include<linux/spi/spidev.h>
#include "spibus.h"

#define SPI_TRANSFER_SPEED_HZ 135000

// Read from SPI Bus /dev/spidev0.0
// fd will be a file descriptor obtained
// by spi_open in spibus.h
// Samples from each element in channels.
// The returned samples are 10-bit.
// The sampl array will be modified to
// contain the samples.
// n_sampl is the number of samples
// to read and the length of channels
// and sampl should be the same
// If diff_pair is != 0 then we will read
// the channel in differential pair mode
// instead of single ended mode
// Returns the status if < 0 then an error occured
int
read_mcp3008(int fd, const unsigned char channels[], int sampl[], int n_sampl, int diff_pair);

#endif
