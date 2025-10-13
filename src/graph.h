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
#define THEME_FONT_NAME_BUF_SZ          64

/* ----- STRUCTS1 ----- */

typedef struct STRUCT_COLOR {
	U8		r;
	U8		g;
	U8		b;
} Color;

typedef struct STRUCT_THEME {
    Color       *color_bg;
    Color       *color_pad;
    Color       *color_tile_body;
    Color       *color_tile_border;
    Color       *color_text_normal;
    Color       *color_text_debug;
    Ch          font_file[THEME_FONT_NAME_BUF_SZ];
} Theme;

typedef struct STRUCT_GAME_SCREEN {
    U16     width;
    U16     height;
    U16     grid_sz;
    U16     grid_width;                 // in px.
    U16     grid_height;                // ""
    U16     tile_border_sz;
    U16     tile_font_sz;
    U16     horiz_pad;
    U16     vert_pad;
    Theme   *theme; 
} GameScreen;

/* ----- FUNCTIONS ----- */

Void init_color(Color *color, U8 r, U8 g, U8 b);

Void init_theme(Theme *theme, Ch *font_file);

Void init_game_screen(GameScreen *game_screen);

Void set_game_screen(GameScreen *game_screen, U16 width, U16 height);

Void init_graphics(GameScreen *game_screen, U16 width, U16 height, Err *err);

Void init_text(GameScreen *game_screen, Err *err);

Void clear_screen(GameScreen *game_screen, Err *err);

Void reload_win(GameScreen *game_screen, Err *err);

Void flip();

Void draw_tile(GameScreen *game_screen, F32 pos_x, F32 pos_y, Ch *letter, Err *err);

Void close_graphics();

#endif
