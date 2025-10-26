/* theme.h - color themes */

#ifndef THEME_H
#define THEME_H

#include "graph.h"
#include "type.h"

#define THEME_FONT_NAME_BUF_SZ          64

typedef struct STRUCT_THEME {
    Color       *color_bg;
    Color       *color_pad;
    Color       *color_tile_body;
    Color       *color_tile_border;
    Color       *color_text_normal;
    Color       *color_text_debug;
    Ch          font_file[THEME_FONT_NAME_BUF_SZ];
} Theme;

Void init_theme(Theme *theme, Ch *font_file);

#endif
