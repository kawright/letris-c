/* tile.c - tile operations */

#include "err.h"
#include "graph.h"
#include "tile.h"
#include "type.h"

Void draw_tile(F32 pos_x, F32 pos_y, Color *fg, Color *bg, Ch *letter, Err *err) {

    // Draw the tile
    set_fg_color(bg);
    draw_rectangle(pos_x, pos_y, 1, 1, err);
    if (is_err(err)) {
        return;
    }
    set_fg_color(fg);
    draw_rectangle(pos_x + LAYOUT_TILE_BORDER_RATIO, pos_y + LAYOUT_TILE_BORDER_RATIO, 
        1 - (2 * LAYOUT_TILE_BORDER_RATIO), 1 - (2 * LAYOUT_TILE_BORDER_RATIO), err);
    if (is_err(err)) {
        return;
    }

    

    // Draw the letter
    F32 text_width;
    F32 text_height;
    guess_text_dim(letter, &text_width, &text_height, err);
    if (is_err(err)) {
        return;
    }
    set_fg_color(bg);
    set_bg_color(fg);
    draw_text_at(pos_x + 0.5 - (0.5 * text_width), pos_y + 0.5 - (0.5 * text_height), letter, err);
    if (is_err(err)) {
        return;
    }

    /*
    SDL_Surface     *temp_surface;
    SDL_Color       temp_color_fg;
                    temp_color_fg.r = game_screen->theme->color_tile_border->r;
                    temp_color_fg.g = game_screen->theme->color_tile_border->g;
                    temp_color_fg.b = game_screen->theme->color_tile_border->b;
    SDL_Color       temp_color_bg;
                    temp_color_bg.r = game_screen->theme->color_tile_body->r;
                    temp_color_bg.g = game_screen->theme->color_tile_body->g;
                    temp_color_bg.b = game_screen->theme->color_tile_body->b;

    temp_surface = TTF_RenderText_Shaded(_tile_font, letter, temp_color_fg, temp_color_bg);
    if (temp_surface == NULL) {
        THROW(err, ERR_GRAPH, "%s\n", "Could not render text")
        return;
    }
    SDL_SetSurfaceBlendMode(temp_surface, SDL_BLENDMODE_NONE);

    U16 text_pos_x = (pos_x * game_screen->grid_sz) + (game_screen->grid_sz / 2) - 
        (temp_surface->w / 2) + game_screen->horiz_pad;
    U16 text_pos_y = (pos_y * game_screen->grid_sz) + (game_screen->grid_sz / 2) - 
        (temp_surface->h / 2) + game_screen->vert_pad;
    SDL_Rect temp_rect = { text_pos_x, text_pos_y, 0, 0 };          // Last two fields are ignored
    if (SDL_BlitSurface(temp_surface, NULL, _surf, &temp_rect) != 0) {
        THROW(err, ERR_GRAPH, "%s\n", "Could not blit text surface")
        SDL_FreeSurface(temp_surface);
        return;
    }
    SDL_FreeSurface(temp_surface);
    */

}
