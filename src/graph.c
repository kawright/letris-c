/* graph.c - low level graphics routines */

#include "debug.h"
#include "err.h"
#include "graph.h"
#include "type.h"

#include <SDL2/SDL.h>


/* ----- PRIVATE VARIABLES ----- */

SDL_Window 		*_win;
SDL_Surface 	*_surf;
SDL_Renderer    *_rend;

/* ----- FUNCTIONS ----- */

Void init_color(Color *color) {
	color->r = 0;
	color->g = 0;
	color->b = 0;
}

Void init_game_screen(GameScreen *game_screen) {
    game_screen->width                  = 0;
    game_screen->height                 = 0;
    game_screen->grid_sz                = 0;
    game_screen->grid_width             = 0;
    game_screen->grid_height            = 0;
    game_screen->tile_border_sz         = 0;
    game_screen->horiz_pad              = 0;
    game_screen->vert_pad               = 0;
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
    
    DEBUG_LOG("%s\n", "Start GameScreen data dump")
    DEBUG_LOG("width:                   %d px\n", game_screen->width)
    DEBUG_LOG("height:                  %d px\n", game_screen->height)
    DEBUG_LOG("grid size:               %d px\n", game_screen->grid_sz)
    DEBUG_LOG("grid width:              %d px\n", game_screen->grid_width)
    DEBUG_LOG("grid height:             %d px\n", game_screen->grid_height)
    DEBUG_LOG("horizontal padding:      %d px\n", game_screen->horiz_pad)
    DEBUG_LOG("vertical padding:        %d px\n", game_screen->vert_pad)
    DEBUG_LOG("tile border size:        %d px\n", game_screen->tile_border_sz)
    DEBUG_LOG("%s\n\n", "End GameScreen data dump")
}

Void init_graphics(GameScreen *game_screen, U16 width, U16 height, Err *err) {
	
	_win 	= NULL;
	_surf 	= NULL;
    _rend   = NULL;
	
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

Void clear_screen(GameScreen *game_screen, Color *bg, Color *pad) {
    SDL_Rect game_screen_rect = {
        game_screen->horiz_pad,
        game_screen->vert_pad,
        game_screen->grid_width,
        game_screen->grid_height
    };
	SDL_FillRect(_surf, NULL, SDL_MapRGB(_surf->format, pad->r, pad->g, pad->b));
    SDL_FillRect(_surf, &game_screen_rect, SDL_MapRGB(_surf->format, bg->r, bg->g, bg->b));
}

Void reload_win() {
    _surf = SDL_GetWindowSurface(_win);
}

Void flip() {
	SDL_UpdateWindowSurface(_win);
    SDL_RenderPresent(_rend);
}

Void close_graphics() {
	SDL_DestroyWindow(_win);
	SDL_Quit();
}

