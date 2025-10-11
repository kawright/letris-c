/* graph.c - low level graphics routines */

#include "err.h"
#include "graph.h"
#include "type.h"

#include <SDL2/SDL.h>


/* ----- PRIVATE VARIABLES ----- */

SDL_Window 		*_win;
SDL_Surface 	*_surf;

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
    game_screen->tile_border_sz         = 0;
    game_screen->horiz_pad              = 0;
    game_screen->vert_pad               = 0;
}

Void init_graphics(GameScreen *game_screen, U16 width, U16 height, Err *err) {
	
	_win 	= NULL;
	_surf 	= NULL;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		THROW(err, ERR_INIT, "Could not initialize SDL video")
		return;
	}

    // Set private variables
	_win = SDL_CreateWindow(DEFAULT_WIN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
	    width, height, SDL_WINDOW_SHOWN);
	if (_win == NULL) {
		THROW(err, ERR_GRAPH, "Could not create a new window")
		SDL_Quit();
		return;
	}
	_surf = SDL_GetWindowSurface(_win);

    // Set game screen data
    game_screen->width              = width;
    game_screen->height             = height;
    
    // Make a guess about the ideal tile size that maximizes at least one side of the entire window
    U16 grid_sz_guess_x     = game_screen->width / LAYOUT_GRID_WIDTH;
    U16 grid_sz_guess_y     = game_screen->height / LAYOUT_GRID_HEIGHT;
    if (grid_sz_guess_x > grid_sz_guess_y) {
        game_screen->grid_sz        = grid_sz_guess_y;
        game_screen->vert_pad       = 0;
        game_screen->horiz_pad      = game_screen->width - ((game_screen->grid_sz * LAYOUT_GRID_WIDTH) / 2);
    } else {
        game_screen->grid_sz        = grid_sz_guess_x;
        game_screen->horiz_pad      = 0;
        game_screen->vert_pad       = game_screen->height - ((game_screen->grid_sz * LAYOUT_GRID_HEIGHT) / 2);
    }

    game_screen->tile_border_sz = game_screen->grid_sz * LAYOUT_TILE_BORDER_RATIO;
}

Void clear_screen(Color *color) {
	SDL_FillRect(_surf, NULL, SDL_MapRGB(_surf->format, color->r, color->g, color->b));
}

Void flip() {
	SDL_UpdateWindowSurface(_win);
}

Void close_graphics() {
	SDL_DestroyWindow(_win);
	SDL_Quit();
}

