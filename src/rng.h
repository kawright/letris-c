/* rng.h - random number generation */

#ifndef RNG_H
#define RNG_H

/* ----- TILE FREQUENCY ----- */

#define FREQ_E      12
#define FREQ_A      9
#define FREQ_I      9
#define FREQ_O      8
#define FREQ_N      6
#define FREQ_R      6
#define FREQ_T      6
#define FREQ_L      4
#define FREQ_S      4
#define FREQ_U      4
#define FREQ_D      4
#define FREQ_G      3
#define FREQ_B      2
#define FREQ_C      2
#define FREQ_M      2
#define FREQ_P      2
#define FREQ_F      2
#define FREQ_H      2
#define FREQ_V      2
#define FREQ_W      2
#define FREQ_Y      2
#define FREQ_K      1
#define FREQ_J      1
#define FREQ_X      1
#define FREQ_Q      1
#define FREQ_Z      1

#include "type.h"

Void reseed();

I32 get_rand_int(I32 max);

/* Uses the same letter distribution as English Scrabble */
Ch get_rand_ch();

#endif
