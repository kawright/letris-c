/* graph.h - low level graphics routines */

#ifndef GRAPH_H
#define GRAPH_H

#include "err.h"
#include "type.h"

/* ----- CONSTANTS ----- */

#define DEFAULT_SCREEN_WIDTH 400
#define DEFAULT_SCREEN_HEIGHT 600
#define DEFAULT_WIN_TITLE "letris"

/* ----- STRUCTS ----- */

typedef struct STRUCT_COLOR {
	U8		r;
	U8		g;
	U8		b;
} Color;

/* ----- FUNCTIONS ----- */

Void init_color(Color *color);

Void init_graphics(Err *err);

Void clear_screen(Color *color);

Void flip();

Void close_graphics();

#endif
