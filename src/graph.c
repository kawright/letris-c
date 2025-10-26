/* graph.c - low level graphics routines */

#include "debug.h"
#include "err.h"
#include "graph.h"
#include "type.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <string.h>

/* ----- PRIVATE STATIC VARIABLES ----- */

static SDL_Window           *_win;
static SDL_Surface          *_surf;
static SDL_Renderer         *_rend;
static TTF_Font             *_font;
static SDL_Color            _bg_color;
static SDL_Color            _fg_color;
static SDL_Color            _pad_color;
static U16                  _win_width;
static U16                  _win_height;
static U16                  _grid_sz;
static U16                  _grid_width; 
static U16                  _grid_height;
static U16                  _tile_border_sz;
static U16                  _tile_font_sz;
static U16                  _horiz_pad;
static U16                  _vert_pad;
static Ch                   _font_file[FONT_FILE_NAME_BUF_SZ];

/* ----- FUNCTIONS ----- */

Void init_color(Color *color, U8 r, U8 g, U8 b) {
	color->r = r;
	color->g = g;
	color->b = b;
}

Void init_graphics(U16 width, U16 height, Ch *font_file, Err *err) {
	
	_win 	            = NULL;
	_surf 	            = NULL;
    _rend               = NULL;
    _font               = NULL;
    _bg_color.r         = 0x00;
    _bg_color.g         = 0x00;
    _bg_color.b         = 0x00;
    _fg_color.r         = 0xff;
    _fg_color.g         = 0xff;
    _fg_color.b         = 0xff;
    _pad_color.r        = 0x00;
    _pad_color.g        = 0x00;
    _pad_color.b        = 0x00;
	
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
    strncpy(_font_file, font_file, FONT_FILE_NAME_BUF_SZ - 1);    

    // Set game screen data
    _win_width          = width;
    _win_height         = height;
    
    // Make a guess about the ideal tile size that maximizes at least one side of the entire window
    U16 grid_sz_guess_x     = _win_width / LAYOUT_GRID_WIDTH;
    U16 grid_sz_guess_y     = _win_height / LAYOUT_GRID_HEIGHT;
    if (grid_sz_guess_x > grid_sz_guess_y) {
        _grid_sz            = grid_sz_guess_y;
        _vert_pad           = 0;
        _horiz_pad          = (_win_width - (_grid_sz * LAYOUT_GRID_WIDTH)) / 2;
    } else {
        _grid_sz            = grid_sz_guess_x;
        _horiz_pad          = 0;
        _vert_pad           = (_win_height - (_grid_sz * LAYOUT_GRID_HEIGHT)) / 2;
    }
    _grid_width             = LAYOUT_GRID_WIDTH * _grid_sz;
    _grid_height            = LAYOUT_GRID_HEIGHT * _grid_sz;

    _tile_border_sz         = _grid_sz * LAYOUT_TILE_BORDER_RATIO;
    _tile_font_sz           = _grid_sz * LAYOUT_TILE_FONT_RATIO;   

    // Load font
    if (TTF_Init() != 0) {
        THROW(err, ERR_INIT, "%s\n", "Could not initialize SDL TTF")
        return;
    } 
    _font = TTF_OpenFont(font_file, _tile_font_sz);
    if (_font == NULL) {
        THROW(err, ERR_INIT, "%s\n", "Could not initialize SDL TTF")
        return;
    }

    DEBUG_LOG("%s\n", "Start GameScreen data dump")
    DEBUG_LOG("width:                   %d px\n", _win_width)
    DEBUG_LOG("height:                  %d px\n", _win_height)
    DEBUG_LOG("grid size:               %d px\n", _grid_sz)
    DEBUG_LOG("grid width:              %d px\n", _grid_width)
    DEBUG_LOG("grid height:             %d px\n", _grid_height)
    DEBUG_LOG("horizontal padding:      %d px\n", _horiz_pad)
    DEBUG_LOG("vertical padding:        %d px\n", _vert_pad)
    DEBUG_LOG("tile border size:        %d px\n", _tile_border_sz)
    DEBUG_LOG("tile font size:          %d px\n", _tile_font_sz)
    DEBUG_LOG("%s\n\n", "End GameScreen data dump")

}


Void clear_screen() {
    SDL_Rect game_screen_rect = {
        _horiz_pad,
        _vert_pad,
        _grid_width,
        _grid_height
    };
	SDL_FillRect(_surf, NULL, SDL_MapRGB(_surf->format, _pad_color.r, _pad_color.g, _pad_color.b));
    SDL_FillRect(_surf, &game_screen_rect, SDL_MapRGB(_surf->format, _bg_color.r, _bg_color.g, _bg_color.b));
}

Void clip_screen() {
    if (_vert_pad > 0) {
        SDL_Rect top_bar = {
            0,
            0,
            _win_width,
            _vert_pad
        };
        SDL_Rect bottom_bar = {
            0,
            _vert_pad + _grid_height,
            _win_width,
            _vert_pad
        };
        SDL_FillRect(_surf, &top_bar, SDL_MapRGB(_surf->format, _pad_color.r, _pad_color.g, _pad_color.b));
        SDL_FillRect(_surf, &bottom_bar, SDL_MapRGB(_surf->format, _pad_color.r, _pad_color.g, _pad_color.b));
    }
}

Void reload_win(Err *err) {
    _surf = SDL_GetWindowSurface(_win);
    _win_width          = _surf->w;
    _win_height         = _surf->h;
    
    // Make a guess about the ideal tile size that maximizes at least one side of the entire window
    U16 grid_sz_guess_x     = _win_width / LAYOUT_GRID_WIDTH;
    U16 grid_sz_guess_y     = _win_height / LAYOUT_GRID_HEIGHT;
    if (grid_sz_guess_x > grid_sz_guess_y) {
        _grid_sz            = grid_sz_guess_y;
        _vert_pad           = 0;
        _horiz_pad          = (_win_width - (_grid_sz * LAYOUT_GRID_WIDTH)) / 2;
    } else {
        _grid_sz            = grid_sz_guess_x;
        _horiz_pad          = 0;
        _vert_pad           = (_win_height - (_grid_sz * LAYOUT_GRID_HEIGHT)) / 2;
    }
    _grid_width             = LAYOUT_GRID_WIDTH * _grid_sz;
    _grid_height            = LAYOUT_GRID_HEIGHT * _grid_sz;

    // Load the font
    _tile_border_sz         = _grid_sz * LAYOUT_TILE_BORDER_RATIO;
    _tile_font_sz           = _grid_sz * LAYOUT_TILE_FONT_RATIO;   
    _font = TTF_OpenFont(_font_file, _tile_font_sz);
    if (_font == NULL) {
        THROW(err, ERR_INIT, "%s\n", "Could not initialize SDL TTF")
        return;
    }
}

Void flip() {
	SDL_UpdateWindowSurface(_win);
    SDL_RenderPresent(_rend);
}


Void close_graphics() {
	SDL_DestroyWindow(_win);
	SDL_Quit();
}

Void draw_text_at(F32 pos_x, F32 pos_y, Ch *text, Err *err) {
    SDL_Surface     *temp_surface;

    temp_surface = TTF_RenderText_Shaded(_font, text, _fg_color, _bg_color);
    if (temp_surface == NULL) {
        THROW(err, ERR_GRAPH, "Could not render text; SDL reported an error: %s\n", TTF_GetError())
        return;
    }
    SDL_SetSurfaceBlendMode(temp_surface, SDL_BLENDMODE_NONE);

    U16 text_pos_x = (pos_x * _grid_sz) + _horiz_pad;
    U16 text_pos_y = (pos_y * _grid_sz) + _vert_pad;
    
    SDL_Rect temp_rect = { text_pos_x, text_pos_y, 0, 0 };          // Last two fields are ignored
    if (SDL_BlitSurface(temp_surface, NULL, _surf, &temp_rect) != 0) {
        THROW(err, ERR_GRAPH, "Could not blit text surface; SDL reported an error: %s\n", TTF_GetError())
        SDL_FreeSurface(temp_surface);
        return;
    }
    SDL_FreeSurface(temp_surface);
}

Void draw_text_center(F32 pos_y, Ch *text, Err *err) {
    F32 text_width;
    F32 text_height;
    guess_text_dim(text, &text_width, &text_height, err);
    if (is_err(err)) {
        return;
    }
    F32 pos_x = ((F32) _win_width) / ((F32) _grid_sz) - (text_width / 2.0);
    draw_text_at(pos_x, pos_y, text, err);
}

Void draw_rectangle(F32 top_left_x, F32 top_left_y, F32 width, F32 height, Err *err) {
    SDL_Rect temp_rect = {
        top_left_x * _grid_sz + _horiz_pad,
        top_left_y * _grid_sz + _vert_pad,
        width * _grid_sz,
        height * _grid_sz 
    };
    SDL_FillRect(_surf, &temp_rect, SDL_MapRGB(_surf->format, _fg_color.r, _fg_color.g, _fg_color.b));
}

Void guess_text_dim(Ch *text, F32 *out_width, F32 *out_height, Err *err) {
    SDL_Surface     *temp_surf;
    temp_surf = TTF_RenderText_Shaded(_font, text, _fg_color, _bg_color);
    if (temp_surf == NULL) {
        THROW(err, ERR_GRAPH, "Could not render text to temporary surface: %s\n", text)
        return;
    }
    *out_width      = ((F32) temp_surf->w) / ((F32) _grid_sz);
    *out_height     = ((F32) temp_surf->h) / ((F32) _grid_sz);
    SDL_FreeSurface(temp_surf);
}

Void set_bg_color(Color *color) {
    _bg_color.r     = color->r;
    _bg_color.g     = color->g;
    _bg_color.b     = color->b;
}

Void set_fg_color(Color *color) {
    _fg_color.r     = color->r;
    _fg_color.g     = color->g;
    _fg_color.b     = color->b;
}

Void set_pad_color(Color *color) {
    _pad_color.r    = color->r;
    _pad_color.g    = color->g;
    _pad_color.b    = color->b;
}

Void set_font(Ch *font_file, F32 size, Err *err) {
    strncpy(_font_file, font_file, FONT_FILE_NAME_BUF_SZ - 1);
    _font = TTF_OpenFont(font_file, size * _grid_sz);
    if (_font == NULL) {
        THROW(err, ERR_INIT, "Could not load font file %s\n", font_file) 
    }
}
