#include "gpio.h"

int
gpio_setup_output(int gpio) {
    int fd;
    char path[64];
    char val[64];

    // For example open file
    // /sys/class/gpio/export
    // and write
    // 4
    strcpy(path,GPIO_PATH);
    strcat(path,"export");
    sprintf(val,"%d",gpio);
    printf("gpio_output: %s %s",path,val);
    fd = open(path,O_WRONLY);
    if(fd == -1) {
        fprintf(stderr,"Exception exporting GPIO %d",gpio);
        return -1;
    }
    write(fd,val,strlen(val)); // TODO will integer work or does it need to be string
    close(fd);

    // Not sure why
    usleep(100000);

    // For example open file
    // /sys/class/gpio/gpio4/direction
    // and write
    // "output"
    strcpy(path,GPIO_PIN_PATH);
    sprintf(val,"%d/direction",gpio);
    strcat(path,val);
    strcpy(val,"output");
    printf("gpio_output: %s %s",path,val);
    fd = open(path,O_WRONLY);
    if(fd == -1) {
        fprintf(stderr,"Exception setting direction on GPIO %d",gpio);
        return -1;
    }
    write(fd,val,strlen(val));
    close(fd);
 
    // For example open file
    // /sys/class/gpio/gpio4/value
    // we will use gpio_write to
    // set the values
    strcpy(path,GPIO_PIN_PATH);
    sprintf(val,"%d/value",gpio);
    strcat(path,val);

    printf("gpio_open: %s",path);
    fd = open(path,O_WRONLY);
    if(fd == -1) {
        fprintf(stderr,"Exception opening GPIO value %d",gpio);
        return -1;
    }
    return fd;
}

int
gpio_open(int gpio) {
    int fd;
    char path[64];
    char val[64];

    // For example open file
    // /sys/class/gpio/gpio4/value
    // we will use gpio_write to
    // set the values
    strcpy(path,GPIO_PIN_PATH);
    sprintf(val,"%d/value",gpio);
    strcat(path,val);

    printf("gpio_open: %s",path);
    fd = open(path,O_WRONLY);
    if(fd == -1) {
        fprintf(stderr,"Exception opening GPIO %d",gpio);
        return -1;
    }
    return fd;
}

int
gpio_write(int fd, int val) {
    return write(fd,&val,1);
}

int
gpio_close(int fd, int gpio) {
    char path[64];

    // close the previously opened fd
    if(close(fd)!=0) {
        fprintf(stderr,"Couldn't close previously opened gpio");
        return -1;
    }

    // For example open file
    // /sys/class/gpio/unexport
    // and write
    // 4
    strcpy(path,GPIO_PATH);
    strcat(path,"unexport");
    printf("gpio_close: %s %d",path,gpio);
    fd = open(path,O_WRONLY);
    if(fd == -1) {
        fprintf(stderr,"Exception unexporting GPIO %d",gpio);
        return -1;
    }
    write(fd,&gpio,1); // TODO will integer work or does it need to be string
    return close(fd);
}
