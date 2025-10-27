/* gamest.h - game state */

#ifndef GAMEST_H
#define GAMEST_H

#include "err.h"
#include "type.h"

/* ----- LEVEL CONSTANTS ----- */

#define LVL_1           0
#define LVL_2           1
#define LVL_3           2
#define LVL_4           3
#define LVL_5           4
#define LVL_6           5
#define LVL_7           6
#define LVL_8           7
#define LVL_CT          8

/* ----- ACCESSORS ----- */

U32 get_score();

U8 get_lvl();

U8 get_free_col();

U8 get_col_height(U8 index, Err *err);

F32 get_drop_spd();

/* ----- MUTATORS ----- */

Void inc_score(U8 amt);

Void inc_lvl();

Void shift_free_col_left();

Void shift_free_col_right();

Void inc_col_height(U8 index, Err *err);                      // Always increments by three

Void dec_col_height(U8 index, Err *err);                      // Always decrements by one

/* ----- INIT FUNCTIONS ----- */

Void init_game_state();

#endif
