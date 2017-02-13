#ifndef SPI_BUS_INCLUDED
#define SPI_BUS_INCLUDED

// See pinout.xyz showing physical pins
// spidev0.0
// CE0 = Pin 24, CE1 = Pin 26, MOSI = Pin 19, MISO = Pin 21, SCLK = Pin 23
// spidev0.1
// CE0 = Pin 12, CE1 = Pin 11, MOSI = Pin 38, MISO = Pin 35, SCLK = Pin 40
#define SPIPATH "/dev/spidev"

// Open the SPI Device
// dev is for example 0.0 in which /dev/spidev will be prepended
// mode is SPIMODE type see
//   https://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus#Mode_numbers
// oflag is O_RDONLY, O_WRONLY, O_RDWR defined in fnctl.h
// returns a file descriptor to the device or -1 on error
int
spi_open(const char dev[], int mode, int oflag);

#endif
