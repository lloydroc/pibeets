# To cross compile from if not compiling on the Pi
# http://www.welzels.de/blog/en/arm-cross-compiling-with-mac-os-x/comment-page-1/
#COMPILER = /usr/local/linaro/arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-gcc
COMPILER = gcc
CFLAGS = -Wall

SRC=$(wildcard *.c)
pibeets: $(SRC)
	$(COMPILER) -o $@ $^ $(CFLAGS)
