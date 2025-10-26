/* theme.c - color themes */

#include "graph.h"
#include "theme.h"
#include "type.h"

#include <string.h>

Void init_theme(Theme *theme, Ch *font_file) {
    theme->color_bg                     = NULL;
    theme->color_pad                    = NULL;
    theme->color_tile_body              = NULL;
    theme->color_tile_border            = NULL;
    theme->color_text_normal            = NULL;
    theme->color_text_debug             = NULL;
    strncpy(theme->font_file, font_file, THEME_FONT_NAME_BUF_SZ - 1);
}

