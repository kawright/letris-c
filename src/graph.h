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

/* ----- OTHER CONSTANTS ----- */

#define DEFAULT_WIN_TITLE               "letris"

/* ----- STRUCTS ----- */

typedef struct STRUCT_COLOR {
	U8		r;
	U8		g;
	U8		b;
} Color;

typedef struct STRUCT_GAME_SCREEN {
    U16     width;
    U16     height;
    U16     grid_sz;
    U16     grid_width;                 // in px.
    U16     grid_height;                // ""
    U16     tile_border_sz;
    U16     horiz_pad;
    U16     vert_pad; 
} GameScreen;

/* ----- FUNCTIONS ----- */

Void init_color(Color *color);

Void init_game_screen(GameScreen *game_screen);

Void set_game_screen(GameScreen *game_screen, U16 width, U16 height);

Void init_graphics(GameScreen *game_screen, U16 width, U16 height, Err *err);

Void clear_screen(GameScreen *game_screen, Color *bg, Color *pad);

Void reload_win();

Void flip();

Void close_graphics();

#endif
