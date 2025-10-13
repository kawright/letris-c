/* graph.c - low level graphics routines */

#include "debug.h"
#include "err.h"
#include "graph.h"
#include "type.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string.h>

/* ----- PRIVATE VARIABLES ----- */

SDL_Window 		*_win;
SDL_Surface 	*_surf;
SDL_Renderer    *_rend;
TTF_Font        *_tile_font;

/* ----- FUNCTIONS ----- */

Void init_color(Color *color, U8 r, U8 g, U8 b) {
	color->r = r;
	color->g = g;
	color->b = b;
}

Void init_game_screen(GameScreen *game_screen) {
    game_screen->width                  = 0;
    game_screen->height                 = 0;
    game_screen->grid_sz                = 0;
    game_screen->grid_width             = 0;
    game_screen->grid_height            = 0;
    game_screen->tile_border_sz         = 0;
    game_screen->tile_font_sz           = 0;
    game_screen->horiz_pad              = 0;
    game_screen->vert_pad               = 0;
    game_screen->theme                  = NULL;
}

Void init_theme(Theme *theme, Ch *font_file) {
    theme->color_bg                     = NULL;
    theme->color_pad                    = NULL;
    theme->color_tile_body              = NULL;
    theme->color_tile_border            = NULL;
    theme->color_text_normal            = NULL;
    theme->color_text_debug             = NULL;
    strncpy(theme->font_file, font_file, THEME_FONT_NAME_BUF_SZ - 1);
}

Void set_game_screen(GameScreen *game_screen, U16 width, U16 height) {

    // Set game screen data
    game_screen->width              = width;
    game_screen->height             = height;
    
    // Make a guess about the ideal tile size that maximizes at least one side of the entire window
    U16 grid_sz_guess_x     = game_screen->width / LAYOUT_GRID_WIDTH;
    U16 grid_sz_guess_y     = game_screen->height / LAYOUT_GRID_HEIGHT;
    if (grid_sz_guess_x > grid_sz_guess_y) {
        game_screen->grid_sz        = grid_sz_guess_y;
        game_screen->vert_pad       = 0;
        game_screen->horiz_pad      = (game_screen->width - (game_screen->grid_sz * LAYOUT_GRID_WIDTH)) / 2;
    } else {
        game_screen->grid_sz        = grid_sz_guess_x;
        game_screen->horiz_pad      = 0;
        game_screen->vert_pad       = (game_screen->height - (game_screen->grid_sz * LAYOUT_GRID_HEIGHT)) / 2;
    }
    game_screen->grid_width = LAYOUT_GRID_WIDTH * game_screen->grid_sz;
    game_screen->grid_height = LAYOUT_GRID_HEIGHT * game_screen->grid_sz;

    game_screen->tile_border_sz = game_screen->grid_sz * LAYOUT_TILE_BORDER_RATIO;
    game_screen->tile_font_sz = game_screen->grid_sz * LAYOUT_TILE_FONT_RATIO;   
 
    DEBUG_LOG("%s\n", "Start GameScreen data dump")
    DEBUG_LOG("width:                   %d px\n", game_screen->width)
    DEBUG_LOG("height:                  %d px\n", game_screen->height)
    DEBUG_LOG("grid size:               %d px\n", game_screen->grid_sz)
    DEBUG_LOG("grid width:              %d px\n", game_screen->grid_width)
    DEBUG_LOG("grid height:             %d px\n", game_screen->grid_height)
    DEBUG_LOG("horizontal padding:      %d px\n", game_screen->horiz_pad)
    DEBUG_LOG("vertical padding:        %d px\n", game_screen->vert_pad)
    DEBUG_LOG("tile border size:        %d px\n", game_screen->tile_border_sz)
    DEBUG_LOG("tile font size:          %d px\n", game_screen->tile_font_sz)
    DEBUG_LOG("%s\n\n", "End GameScreen data dump")
}

Void init_graphics(GameScreen *game_screen, U16 width, U16 height, Err *err) {
	
	_win 	            = NULL;
	_surf 	            = NULL;
    _rend               = NULL;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		THROW(err, ERR_INIT, "Could not initialize SDL video")
		return;
	}

    // Set private variables
	_win = SDL_CreateWindow(DEFAULT_WIN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
	    width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (_win == NULL) {
		THROW(err, ERR_GRAPH, "Could not create a new window")
		SDL_Quit();
		return;
	}
	_surf = SDL_GetWindowSurface(_win);
    _rend = SDL_CreateRenderer(_win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    set_game_screen(game_screen, width, height);

}

Void init_text(GameScreen *game_screen, Err *err) {
    if (game_screen->theme == NULL) {
        THROW(err, ERR_DATA, "%s\n", "Cannot initialize text: game_screen->theme is NULL")
        return; 
    }
    _tile_font = NULL;
    _tile_font = TTF_OpenFont(game_screen->theme->font_file, game_screen->tile_font_sz);
    if (_tile_font == NULL) {
        THROW(err, ERR_INIT, "%s\n", "Could not initialize SDL TTF")
        return;
    }
}

Void clear_screen(GameScreen *game_screen, Err *err) {
    SDL_Rect game_screen_rect = {
        game_screen->horiz_pad,
        game_screen->vert_pad,
        game_screen->grid_width,
        game_screen->grid_height
    };
    if (game_screen->theme == NULL) {
        THROW(err, ERR_DATA, "%s\n", "Cannot clear screen: game_screen->theme is NULL");
    }
    if (game_screen->theme->color_bg == NULL) {
        THROW(err, ERR_DATA, "%s\n", "Cannot clear screen: game_screen->theme->color_bg is NULL")
        return;
    }
    if (game_screen->theme->color_pad == NULL) {
        THROW(err, ERR_DATA, "%s\n", "Cannot clear screen: game_screen->theme->color_pad is NULL")
        return;
    }
	SDL_FillRect(_surf, NULL, SDL_MapRGB(_surf->format, game_screen->theme->color_pad->r, 
        game_screen->theme->color_pad->g, game_screen->theme->color_pad->b));
    SDL_FillRect(_surf, &game_screen_rect, SDL_MapRGB(_surf->format, game_screen->theme->color_bg->r, 
        game_screen->theme->color_bg->g, game_screen->theme->color_bg->b));
}

Void reload_win() {
    _surf = SDL_GetWindowSurface(_win);
}

Void flip() {
	SDL_UpdateWindowSurface(_win);
    SDL_RenderPresent(_rend);
}

Void draw_tile(GameScreen *game_screen, F32 pos_x, F32 pos_y, Err *err) {
    if (game_screen->theme == NULL) {
        THROW(err, ERR_DATA, "%s\n", "Cannot draw tile: game_screen->theme is NULL")
        return;
    }
    if (game_screen->theme->color_tile_body == NULL) {
        THROW(err, ERR_DATA, "%s\n", "Cannot draw tile: game_screen->theme->color_tile_body is NULL")
        return;
    }
    if (game_screen->theme->color_tile_border == NULL) {
        THROW(err, ERR_DATA, "%s\n", "Cannot draw tile: game_screen->theme->color_tile_border is NULL")
        return;
    }
    SDL_Rect outer_rect = {
        pos_x * game_screen->grid_sz + game_screen->horiz_pad,
        pos_y * game_screen->grid_sz + game_screen->vert_pad,
        game_screen->grid_sz,
        game_screen->grid_sz
    };
    SDL_Rect inner_rect = {
        (pos_x * game_screen->grid_sz) + game_screen->tile_border_sz + game_screen->horiz_pad,
        (pos_y * game_screen->grid_sz) + game_screen->tile_border_sz + game_screen->vert_pad,
        game_screen->grid_sz - (2 * game_screen->tile_border_sz),
        game_screen->grid_sz - (2 * game_screen->tile_border_sz)
    };
    SDL_FillRect(_surf, &outer_rect, SDL_MapRGB(_surf->format, game_screen->theme->color_tile_border->r, 
        game_screen->theme->color_tile_border->g, game_screen->theme->color_tile_border->b));
    SDL_FillRect(_surf, &inner_rect, SDL_MapRGB(_surf->format, game_screen->theme->color_tile_body->r, 
        game_screen->theme->color_tile_body->g, game_screen->theme->color_tile_body->b));
    
}

Void close_graphics() {
	SDL_DestroyWindow(_win);
	SDL_Quit();
}

