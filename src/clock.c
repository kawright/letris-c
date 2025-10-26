/* clock.c - stopwatch functions */

#include "clock.h"
#include "type.h"

#include <stdlib.h>
#include <sys/time.h>


Void init_clock(Clock *clock) {
    struct timeval time_val;
    gettimeofday(&time_val, NULL);
    *clock = (Clock)(time_val.tv_sec) * 1000 + (Clock)(time_val.tv_usec) / 1000;
}

U32 tick_clock(Clock *clock) {
    Clock temp_clock = *clock;
    struct timeval time_val;
    gettimeofday(&time_val, NULL);
    *clock = (Clock)(time_val.tv_sec) * 1000 + (Clock)(time_val.tv_usec) / 1000;
    return (U32) *clock - temp_clock;
}
