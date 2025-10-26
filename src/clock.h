/* clock.h - stopwatch functions */

#ifndef CLOCK_H
#define CLOCK_H

#include "type.h"

typedef U64 Clock;

Void init_clock(Clock *clock);

U32 tick_clock(Clock *clock);

#endif
