/* rng.c - random number generation */

#include "rng.h"
#include "type.h"

#include <stdlib.h>
#include <sys/time.h>

static I32      _seed; 

Void reseed() {
    struct timeval time_val;
    gettimeofday(&time_val, NULL);
    _seed = ((time_val.tv_sec * 1000) + time_val.tv_usec) / 1000;
    srand(_seed);
}

I32 get_rand_int(I32 max) {
    I32 return_data = rand();
    return return_data % max;  
}

Ch get_rand_ch() {
    I32 rand_int    = get_rand_int(97);
    if (rand_int < FREQ_A) {
        return 'a';
    }
    if (rand_int < FREQ_A + FREQ_B) {
        return 'b';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C) {
        return 'c';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D) {
        return 'd';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E) {
        return 'e';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F) {
        return 'f';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G) {
        return 'g';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H) {
        return 'h';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H + FREQ_I) {
        return 'i';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H + FREQ_I + FREQ_J) {
        return 'j';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H + FREQ_I + FREQ_J + FREQ_K) {
        return 'k';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H + FREQ_I + FREQ_J + FREQ_K
            + FREQ_L) {
        return 'l';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H + FREQ_I + FREQ_J + FREQ_K
            + FREQ_L + FREQ_M) {
        return 'm';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H + FREQ_I + FREQ_J + FREQ_K
            + FREQ_L + FREQ_M + FREQ_N) {
        return 'n';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H + FREQ_I + FREQ_J + FREQ_K
            + FREQ_L + FREQ_M + FREQ_N + FREQ_O) {
        return 'o';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H + FREQ_I + FREQ_J + FREQ_K
            + FREQ_L + FREQ_M + FREQ_N + FREQ_O + FREQ_P) {
        return 'p';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H + FREQ_I + FREQ_J + FREQ_K
            + FREQ_L + FREQ_M + FREQ_N + FREQ_O + FREQ_P + FREQ_Q) {
        return 'q';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H + FREQ_I + FREQ_J + FREQ_K
            + FREQ_L + FREQ_M + FREQ_N + FREQ_O + FREQ_P + FREQ_Q + FREQ_R) {
        return 'r';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H + FREQ_I + FREQ_J + FREQ_K
            + FREQ_L + FREQ_M + FREQ_N + FREQ_O + FREQ_P + FREQ_Q + FREQ_R + FREQ_S) {
        return 's';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H + FREQ_I + FREQ_J + FREQ_K
            + FREQ_L + FREQ_M + FREQ_N + FREQ_O + FREQ_P + FREQ_Q + FREQ_R + FREQ_S + FREQ_T) {
        return 't';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H + FREQ_I + FREQ_J + FREQ_K
            + FREQ_L + FREQ_M + FREQ_N + FREQ_O + FREQ_P + FREQ_Q + FREQ_R + FREQ_S + FREQ_T + FREQ_U) {
        return 'u';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H + FREQ_I + FREQ_J + FREQ_K
            + FREQ_L + FREQ_M + FREQ_N + FREQ_O + FREQ_P + FREQ_Q + FREQ_R + FREQ_S + FREQ_T + FREQ_U + FREQ_V) {
        return 'v';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H + FREQ_I + FREQ_J + FREQ_K
            + FREQ_L + FREQ_M + FREQ_N + FREQ_O + FREQ_P + FREQ_Q + FREQ_R + FREQ_S + FREQ_T + FREQ_U + FREQ_V
            + FREQ_W) {
        return 'w';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H + FREQ_I + FREQ_J + FREQ_K
            + FREQ_L + FREQ_M + FREQ_N + FREQ_O + FREQ_P + FREQ_Q + FREQ_R + FREQ_S + FREQ_T + FREQ_U + FREQ_V
            + FREQ_W + FREQ_X) {
        return 'x';
    }
    if (rand_int < FREQ_A + FREQ_B + FREQ_C + FREQ_D + FREQ_E + FREQ_F + FREQ_G + FREQ_H + FREQ_I + FREQ_J + FREQ_K
            + FREQ_L + FREQ_M + FREQ_N + FREQ_O + FREQ_P + FREQ_Q + FREQ_R + FREQ_S + FREQ_T + FREQ_U + FREQ_V
            + FREQ_W + FREQ_X + FREQ_Y) {
        return 'y';
    }
    return 'z';
}
