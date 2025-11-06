/* tile.c - tile operations */

#include "debug.h"
#include "err.h"
#include "graph.h"
#include "tile.h"
#include "type.h"

#include <stdlib.h>
#include <string.h>

Void init_tile_matrix(TileMatrix *matrix, U8 width, U8 height) {
    matrix->pos_x               = 0;
    matrix->pos_y               = 0;
    matrix->width               = width;
    matrix->height              = height;
    for (U8 row = 0; row < matrix->height; row++) {
        for (U8 col = 0; col < matrix->width; col++) {
            matrix->matrix[row][col] = '\0';
        }
    }
}

Ch get_tile_from_matrix(TileMatrix *matrix, U8 column, U8 row, Err *err) {
    if (column >= matrix->width) {
        THROW(err, ERR_DATA, "%s\n", "Out of bounds tile matrix access")
        return '\0';
    }
    if (row >= matrix->height) {
        THROW(err, ERR_DATA, "%s\n", "Out of bounds tile matrix access")
        return '\0';
    }
    return matrix->matrix[row][column];
}

Void set_tile_in_matrix(TileMatrix *matrix, Ch letter, U8 column, U8 row, Err *err) {
    if (column >= matrix->width) {
        THROW(err, ERR_DATA, "%s\n", "Out of bounds tile matrix access")
        return;
    }
    if (row >= matrix->height) {
        THROW(err, ERR_DATA, "%s\n", "Out of bounds tile matrix access")
        return;
    }
    matrix->matrix[row][column] = letter;
}

Void draw_tile(F32 pos_x, F32 pos_y, Color *fg, Color *bg, Ch letter, Err *err) {

    // Draw the tile
    set_fg_color(bg);
    draw_rectangle(pos_x, pos_y, 1, 1, err);
    if (is_err(err)) {
        return;
    }
    set_fg_color(fg);
    draw_rectangle(pos_x +  LAYOUT_TILE_BORDER_RATIO, pos_y + LAYOUT_TILE_BORDER_RATIO, 
        1 - (2 * LAYOUT_TILE_BORDER_RATIO), 1 - (2 * LAYOUT_TILE_BORDER_RATIO), err);
    if (is_err(err)) {
        return;
    }
    
    // Draw the letter
    F32     text_width;
    F32     text_height;
    Ch      temp_str[2];
    temp_str[0] = letter;
    temp_str[1] = '\0';
    guess_text_dim(temp_str, &text_width, &text_height, err);
    if (is_err(err)) {
        return;
    }
    set_fg_color(bg);
    set_bg_color(fg);
    draw_text_at(pos_x + 0.5 - (0.5 * text_width), pos_y + 0.5 - (0.5 * text_height), temp_str, err);
    if (is_err(err)) {
        return;
    }

}

Void draw_tile_matrix(Color *fg, Color *bg, TileMatrix *matrix, Err *err) {
    Ch curr_letter;
    for (U8 row = 0; row < matrix->height; row++) {
        for (U8 col = 0; col < matrix->width; col++) {
            curr_letter = get_tile_from_matrix(matrix, col, row, err);
            if (is_err(err)) {
                return;
            }
            if (curr_letter != '\0') {
                draw_tile(matrix->pos_x + col, matrix->pos_y + row, fg, bg, curr_letter, err);
                if (is_err(err)) {
                    return;
                } 
            }
        }
    }
}

