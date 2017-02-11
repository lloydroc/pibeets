# pibeets - Music Beats coupled with WS2801 LED Strip
Use the Raspberry PI to Sample Audio from a MCP3008 10-bit ADC, perform signal processing for beat detection and display those beets on a WS2801 LED Strip.

## Setup
We must enable `spi` on the Raspberry Pi we must edit `/boot/config.txt` as root and have this line in config: `dtparam=spi=on`. A reboot of the Pi is necessary to have SPI on and can be checked by confirming the `spi` kernel module is enabled:

```
pi@raspberrypi:~ $ lsmod | grep spi
spi_bcm2835             7424  0
pi@raspberrypi:~ $ ls /dev/spidev*
/dev/spidev0.0  /dev/spidev0.1
```

## Required
We used Rasbian Jesse for this

1. `ansible` - We use ansible to copy the source, build it, test it and run it

## References
[MCP3008 Datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/21295d.pdf "MCP3008 Datasheet")
[MCP3208 Datasheet for Reference](http://ww1.microchip.com/downloads/en/DeviceDoc/21298e.pdf)
[RPi MCP3208 SPI by Derek Molloy](https://github.com/derekmolloy/exploringrpi/tree/master/chp10/tmp36)
