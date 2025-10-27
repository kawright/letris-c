/* tile.h - tile operations */

#ifndef TILE_H
#define TILE_H

#include "err.h"
#include "graph.h"
#include "type.h"

/* ----- CONSTANTS ----- */

#define TILE_LETTER_BUF_SZ      3
#define TILE_DROP_SPD			0.8

/* ----- TYPES ----- */

typedef struct STRUCT_TILE_MATRIX {
    F32     pos_x;
    F32     pos_y;
    U8      width;
    U8      height;
    Ch      matrix[LAYOUT_GRID_HEIGHT][LAYOUT_GRID_WIDTH][TILE_LETTER_BUF_SZ];
} TileMatrix;

/* ----- TILE MATRIX FUNCTIONS ----- */

Void init_tile_matrix(TileMatrix *matrix, U8 width, U8 height);

Ch *get_tile_from_matrix(TileMatrix *matrix, U8 column, U8 row, Err *err);

Void set_tile_in_matrix(TileMatrix *matrix, Ch *letter, U8 column, U8 row, Err *err);

/* ----- DRAW FUNCTIONS ----- */

Void draw_tile(F32 pos_x, F32 pos_y, Color *fg, Color *bg, Ch *letter, Err *err);

Void draw_tile_matrix(Color *fg, Color *bg, TileMatrix *matrix, Err *err);

#endif
