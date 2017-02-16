#include "util.h"
#include <stdio.h>

void print_timetaken(char label[], struct timeval start, struct timeval end) {
    double usec,sec;
    usec = (double) (end.tv_usec - start.tv_usec)/1000000;
    sec  = (double) (end.tv_sec - start.tv_sec);
    printf("%s: Time Taken = %f\n",label,sec+usec);
}
