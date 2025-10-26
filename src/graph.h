/* graph.h - low level graphics routines */

#ifndef GRAPH_H
#define GRAPH_H

#include "err.h"
#include "type.h"

/* ----- DEFAULTS ----- */

#define DEFAULT_SCREEN_WIDTH            400
#define DEFAULT_SCREEN_HEIGHT           600

/* ----- LAYOUT CONSTANTS ----- */

#define LAYOUT_GRID_WIDTH               6                   // In tile space, not px. space
#define LAYOUT_GRID_HEIGHT              12                  // ""
#define LAYOUT_TILE_BORDER_RATIO        0.1                 // Tile border to side-length ratio
#define LAYOUT_TILE_FONT_RATIO          0.5

/* ----- OTHER CONSTANTS ----- */

#define DEFAULT_WIN_TITLE               "letris"
#define FONT_FILE_NAME_BUF_SZ           128

/* ----- STRUCTS ----- */

typedef struct STRUCT_COLOR {
	U8		r;
	U8		g;
	U8		b;
} Color;

/* ----- SUBSYSTEM FUNCTIONS ----- */

Void init_graphics(U16 width, U16 height, Ch *font_file, Err *err);

Void close_graphics();

/* ----- COLOR FUNCTIONS ----- */

Void init_color(Color *color, U8 r, U8 g, U8 b);

/* ----- WINDOW FUNCTIONS ----- */

Void clear_screen();

Void reload_win(Err *err);

Void flip();

/* ----- DRAWING STATE ----- */

Void set_bg_color(Color *color);

Void set_fg_color(Color *color);

Void set_pad_color(Color *color);

Void set_font(Ch *font_file, F32 size, Err *err);

/* ----- DRAWING ROUTINES ----- */

Void draw_text_at(F32 pos_x, F32 pos_y, Ch *text, Err *err);

Void draw_text_center(F32 pos_y, Ch *text, Err *err);

Void draw_rectangle(F32 top_left_x, F32 top_left_y, F32 width, F32 height, Err *err);

F32 guess_text_width(Ch *text, Err *err);           // DEPRECATED

Void guess_text_dim(Ch *text, F32 *out_width, F32 *out_height, Err *err);

#endif
