/* gamest.c - game state */

#include "gamest.h"
#include "graph.h"
#include "type.h"

/* ----- PRIVATE STATIC VARIABLES ----- */

static U32          _score;
static U8           _lvl;
static U8           _free_col;
static U8           _col_height[LAYOUT_GRID_WIDTH];
static F32          _lvl_drop_spds[LVL_CT]; 

Void init_game_state() {
    _score          = 0;
    _lvl            = LVL_1;
    _free_col       = 0;
    for (U8 i = 0; i < LAYOUT_GRID_WIDTH; i++) {
        _col_height[i] = 0;
    }
    _lvl_drop_spds[LVL_1] = 0.8;
    _lvl_drop_spds[LVL_2] = 1.0;
    _lvl_drop_spds[LVL_3] = 1.2;
    _lvl_drop_spds[LVL_4] = 1.5;
    _lvl_drop_spds[LVL_5] = 1.75;
    _lvl_drop_spds[LVL_6] = 2.0;
    _lvl_drop_spds[LVL_7] = 2.5;
    _lvl_drop_spds[LVL_8] = 3.0;
}

U32 get_score() {
    return _score;
}

U8 get_lvl() {
    return _lvl;
}

U8 get_free_col() {
    return _free_col;
}

U8 get_col_height(U8 index, Err *err) {
    if (index >= LAYOUT_GRID_WIDTH) {
        THROW(err, ERR_DATA, "Attempted out-of-bounds array access at index %d\n", index)
        return 0;
    }
    return _col_height[index];
}

F32 get_drop_spd() {
    return _lvl_drop_spds[_lvl];
}

Void inc_score(U8 amt) {
    _score += amt;
}

Void inc_lvl() {
    if (_lvl >= LVL_8) {
        return;
    }
    _lvl++;
}

Void shift_free_col_left() {
    if (_free_col == 0) {
        return;
    }
    _free_col--;
}

Void shift_free_col_right() {
    if (_free_col >= LAYOUT_GRID_WIDTH - 1) {
        return;
    }
    _free_col++;
}

Void inc_col_height(U8 index, Err *err) {
    if (index >= LAYOUT_GRID_WIDTH) {
        THROW(err, ERR_DATA, "Attempted out-of-bounds array access at index %d\n", index)
        return ;
    }
    _col_height[index] += LAYOUT_FREE_TILE_COUNT;
}

Void dec_col_height(U8 index, Err *err) {
    if (index >= LAYOUT_GRID_WIDTH) {
        THROW(err, ERR_DATA, "Attempted out-of-bounds array access at index %d\n", index)
        return ;
    }
    if (_col_height[index] == 0) {
        return;
    }
    _col_height[index]--;
}

