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
    printf("gpio_setup_output: %s %s\n",path,val);
    fd = open(path,O_WRONLY);
    if(fd == -1) {
        fprintf(stderr,"Exception exporting GPIO %d",gpio);
        return -1;
    }
    if(write(fd,val,strlen(val))<0) {
        perror("GPIO: Unable to set output");
    }
    close(fd);

    // After we export the pin the
    // driver will create a new directory
    // for us in /sys/class/gpio/gpio%d
    usleep(100000);

    // For example open file
    // /sys/class/gpio/gpio4/direction
    // and write
    // "out"
    strcpy(path,GPIO_PIN_PATH);
    sprintf(val,"%d/direction",gpio);
    strcat(path,val);
    strcpy(val,"out");
    printf("gpio_setup_output: %s %s\n",path,val);
    fd = open(path,O_WRONLY);
    if(fd == -1) {
        fprintf(stderr,"Exception setting direction on GPIO %d",gpio);
        return -1;
    }
    if(write(fd,val,strlen(val))<0) {
        perror("GPIO: Unable to setup output");
    }
    close(fd);

    // For example open file
    // /sys/class/gpio/gpio4/value
    // we will use gpio_write to
    // set the values
    strcpy(path,GPIO_PIN_PATH);
    sprintf(val,"%d/value",gpio);
    strcat(path,val);

    printf("gpio_setup_output: %s\n",path);
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

    printf("gpio_open: %s\n",path);
    fd = open(path,O_WRONLY);
    if(fd == -1) {
        fprintf(stderr,"Exception opening GPIO %d",gpio);
        return -1;
    }
    return fd;
}

int
gpio_write(int fd, int val) {
    char cval[4];
    sprintf(cval,"%d",val);
    printf("gpio_write: %s\n",cval);
    int ret = write(fd,cval,strlen(cval));
    if(ret<0)
        perror("GPIO: unable to perform gpio write");
    return ret;
}

int
gpio_close(int fd, int gpio) {
    char path[64];
    char val[64];
    sprintf(val,"%d",gpio);

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
    printf("gpio_close: %s %d\n",path,gpio);
    fd = open(path,O_WRONLY);
    if(fd == -1) {
        fprintf(stderr,"Exception unexporting GPIO %d",gpio);
        return -1;
    }
    if(write(fd,val,strlen(val))<0) {
        perror("GPIO: Unable to unexport gpio");
    };
    return close(fd);
}
