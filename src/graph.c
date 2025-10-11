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

Void init_graphics(Err *err) {
	
	_win 	= NULL;
	_surf 	= NULL;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		THROW(err, ERR_INIT, "Could not initialize SDL video")
		return;
	}
	_win = SDL_CreateWindow(DEFAULT_WIN_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
		DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (_win == NULL) {
		THROW(err, ERR_GRAPH, "Could not create a new window")
		SDL_Quit();
		return;
	}
	_surf = SDL_GetWindowSurface(_win);
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

