#ifndef UTIL_DEFINED
#define UTIL_DEFINED

#include<sys/time.h>

// Utility functions for the project

// Print the time it took for something to complete
void print_timetaken(char label[], struct timeval start, struct timeval end);

#endif
