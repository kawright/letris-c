/* main.c - entry point */

#include "clock.h"
#include "debug.h"
#include "err.h"
#include "event.h"
#include "graph.h"
#include "tile.h"
#include "theme.h"
#include "type.h"

#include <stdio.h>
#include <SDL2/SDL.h>

/* ----- THEME NAMES ----- */

#define THEME_CLASSIC           0
#define THEME_RED               1
#define THEME_YELLOW            2
#define THEME_BLUE              3
#define THEME_PINK_GREEN        4
#define THEME_GREEN_TEAL        5
#define THEME_BROWN             6
#define THEME_BLACK             7

I16 main(I16 argc, Ch **argv) {

    Err err;
    init_err(&err);

    init_graphics(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, "./asset/font/Caprasimo.ttf", &err);
    if (is_err(&err)) {
        warn(&err);
        return err.code;
    }

    // Initialize colors...

    // Purples:
    Color color_slate_blue;                     init_color(&color_slate_blue, 106, 90, 205);
    Color color_medium_slate_blue;              init_color(&color_medium_slate_blue, 123, 104, 238);
    Color color_dark_slate_blue;                init_color(&color_dark_slate_blue, 72, 61, 139);
    Color color_violet;                         init_color(&color_violet, 238, 130, 238);
    Color color_dark_violet;                    init_color(&color_dark_violet, 148, 0, 211);
    Color color_blue_violet;                    init_color(&color_blue_violet, 138, 43, 226);

    // Pinks:
    Color color_medium_violet_red;              init_color(&color_medium_violet_red, 199, 21, 133);
    Color color_deep_pink;                      init_color(&color_deep_pink, 255, 20, 147);
    Color color_hot_pink;                       init_color(&color_hot_pink, 255, 105, 180);

    // Reds:
    Color color_red;                            init_color(&color_red, 255, 0, 0);
    Color color_dark_red;                       init_color(&color_dark_red, 139, 0, 0);
    Color color_crimson;                        init_color(&color_crimson, 220, 20, 60);
    Color color_salmon;                         init_color(&color_salmon, 250, 128, 114);
    Color color_light_salmon;                   init_color(&color_light_salmon, 255, 160, 122);
    Color color_dark_salmon;                    init_color(&color_dark_salmon, 233, 150, 122);

    // Orange:
    Color color_orange_red;                     init_color(&color_orange_red, 255, 69, 0);
    Color color_dark_orange;                    init_color(&color_dark_orange, 255, 140, 0);
    Color color_orange;                         init_color(&color_orange, 255, 165, 0);

    // Yellows:
    Color color_yellow;                         init_color(&color_yellow, 255, 255, 0);
    Color color_light_yellow;                   init_color(&color_light_yellow, 255, 255, 224);
    Color color_gold;                           init_color(&color_gold, 255, 215, 0);
    Color color_papaya_whip;                    init_color(&color_papaya_whip, 255, 239, 213);

    // Blues:
    Color color_blue;                           init_color(&color_blue, 0, 0, 255);
    Color color_medium_blue;                    init_color(&color_medium_blue, 0, 0, 205);
    Color color_dark_blue;                      init_color(&color_dark_blue, 0, 0, 139);
    Color color_dodger_blue;                    init_color(&color_dodger_blue, 30, 144, 255);
    Color color_sky_blue;                       init_color(&color_sky_blue, 135, 206, 250);
    Color color_deep_sky_blue;                  init_color(&color_deep_sky_blue, 0, 191, 255);

    // Browns:
    Color color_brown;                          init_color(&color_brown, 165, 42, 42);
    Color color_saddle_brown;                   init_color(&color_saddle_brown, 139, 69, 19);
    Color color_chocolate;                      init_color(&color_chocolate, 210, 105, 30);
    Color color_sienna;                         init_color(&color_sienna, 160, 82, 45);

    // Teals:
    Color color_turquoise;                      init_color(&color_turquoise, 64, 224, 208);
    Color color_medium_turquoise;               init_color(&color_medium_turquoise, 72, 209, 204);
    Color color_dark_turquoise;                 init_color(&color_dark_turquoise, 0, 206, 209);
    Color color_aquamarine;                     init_color(&color_aquamarine, 127, 255, 212);

    // Greens:
    Color color_green;                          init_color(&color_green, 0, 128, 0);
    Color color_dark_green;                     init_color(&color_dark_green, 0, 100, 0);
    Color color_chartreuse;                     init_color(&color_chartreuse, 127, 255, 0);
    Color color_lime;                           init_color(&color_lime, 0, 255, 0);
    Color color_green_yellow;                   init_color(&color_green_yellow, 173, 255, 47);

    // Whites:
    Color color_white;                          init_color(&color_white, 255, 255, 255);
    Color color_antique_white;                  init_color(&color_antique_white, 250, 235, 215);
    Color color_linen;                          init_color(&color_linen, 250, 240, 230);
    Color color_beige;                          init_color(&color_beige, 245, 245, 220);

    // Blacks/Grays
    Color color_black;                          init_color(&color_black, 0, 0, 0);
    Color color_slate_gray;                     init_color(&color_slate_gray, 112, 128, 144);
    Color color_light_slate_gray;               init_color(&color_light_slate_gray, 119, 136, 153);
    Color color_dark_slate_gray;                init_color(&color_dark_slate_gray, 47, 79, 79);
    Color color_gainsboro;                      init_color(&color_gainsboro, 220, 220, 220);
    Color color_silver;                         init_color(&color_silver, 192, 192, 192);

    // Initialize Themes:
 
    Theme themes[8];
 
    init_theme(&themes[THEME_CLASSIC], "./asset/font/Caprasimo.ttf");
    themes[THEME_CLASSIC].color_bg                          = &color_slate_blue;
    themes[THEME_CLASSIC].color_pad                         = &color_dark_slate_blue;
    themes[THEME_CLASSIC].color_tile_body                   = &color_papaya_whip;
    themes[THEME_CLASSIC].color_tile_border                 = &color_dark_orange;
    themes[THEME_CLASSIC].color_text_normal                 = &color_white;
    themes[THEME_CLASSIC].color_text_debug                  = &color_white;
   
    init_theme(&themes[THEME_RED], "./asset/font/Caprasimo.ttf");
    themes[THEME_RED].color_bg                              = &color_crimson;
    themes[THEME_RED].color_pad                             = &color_dark_red;
    themes[THEME_RED].color_tile_body                       = &color_white;
    themes[THEME_RED].color_tile_border                     = &color_red;
    themes[THEME_RED].color_text_normal                     = &color_white;
    themes[THEME_RED].color_text_debug                      = &color_white;
    
    init_theme(&themes[THEME_YELLOW], "./asset/font/Caprasimo.ttf");
    themes[THEME_YELLOW].color_bg                           = &color_yellow;
    themes[THEME_YELLOW].color_pad                          = &color_gold;
    themes[THEME_YELLOW].color_tile_body                    = &color_papaya_whip;
    themes[THEME_YELLOW].color_tile_border                  = &color_dark_orange;
    themes[THEME_YELLOW].color_text_normal                  = &color_white;
    themes[THEME_YELLOW].color_text_debug                   = &color_white;
    
    init_theme(&themes[THEME_BLUE], "./asset/font/Caprasimo.ttf");
    themes[THEME_BLUE].color_bg                             = &color_medium_blue;
    themes[THEME_BLUE].color_pad                            = &color_dark_blue;
    themes[THEME_BLUE].color_tile_body                      = &color_white;
    themes[THEME_BLUE].color_tile_border                    = &color_deep_sky_blue;
    themes[THEME_BLUE].color_text_normal                    = &color_white;
    themes[THEME_BLUE].color_text_debug                     = &color_white;
    
    init_theme(&themes[THEME_PINK_GREEN], "./asset/font/Caprasimo.ttf");
    themes[THEME_PINK_GREEN].color_bg                       = &color_hot_pink;
    themes[THEME_PINK_GREEN].color_pad                      = &color_deep_pink;
    themes[THEME_PINK_GREEN].color_tile_body                = &color_white;
    themes[THEME_PINK_GREEN].color_tile_border              = &color_chartreuse;
    themes[THEME_PINK_GREEN].color_text_normal              = &color_white;
    themes[THEME_PINK_GREEN].color_text_debug               = &color_white;
    
    init_theme(&themes[THEME_GREEN_TEAL], "./asset/font/Caprasimo.ttf");
    themes[THEME_GREEN_TEAL].color_bg                       = &color_green;
    themes[THEME_GREEN_TEAL].color_pad                      = &color_dark_green;
    themes[THEME_GREEN_TEAL].color_tile_body                = &color_white;
    themes[THEME_GREEN_TEAL].color_tile_border              = &color_medium_turquoise;
    themes[THEME_GREEN_TEAL].color_text_normal              = &color_white;
    themes[THEME_GREEN_TEAL].color_text_debug               = &color_white;
    
    init_theme(&themes[THEME_BROWN], "./asset/font/Caprasimo.ttf");
    themes[THEME_BROWN].color_bg                            = &color_sienna;
    themes[THEME_BROWN].color_pad                           = &color_saddle_brown;
    themes[THEME_BROWN].color_tile_body                     = &color_beige;
    themes[THEME_BROWN].color_tile_border                   = &color_chocolate;
    themes[THEME_BROWN].color_text_normal                   = &color_white;
    themes[THEME_BROWN].color_text_debug                    = &color_white;
    
    init_theme(&themes[THEME_BLACK], "./asset/font/Caprasimo.ttf");
    themes[THEME_BLACK].color_bg                            = &color_silver;
    themes[THEME_BLACK].color_pad                           = &color_gainsboro;
    themes[THEME_BLACK].color_tile_body                     = &color_white;
    themes[THEME_BLACK].color_tile_border                   = &color_black;
    themes[THEME_BLACK].color_text_normal                   = &color_white;
    themes[THEME_BLACK].color_text_debug                    = &color_white;

    U8 current_theme        = 0;

    // Initialize tile matrices
    TileMatrix      matrix_placed;
    TileMatrix      matrix_free;
    TileMatrix      matrix_shift;
    init_tile_matrix(&matrix_placed, LAYOUT_GRID_WIDTH, LAYOUT_GRID_HEIGHT);
    init_tile_matrix(&matrix_free, 1, LAYOUT_FREE_TILE_COUNT);
    init_tile_matrix(&matrix_shift, LAYOUT_GRID_WIDTH, LAYOUT_GRID_HEIGHT);
	matrix_free.pos_x = 2.5;
	matrix_free.pos_y = (-4.0);
	set_tile_in_matrix(&matrix_free, "a", 0, 0, NULL);
	set_tile_in_matrix(&matrix_free, "b", 0, 1, NULL);
	set_tile_in_matrix(&matrix_free, "c", 0, 2, NULL);

	Clock 	clock;
	init_clock(&clock);

	Event event;
    Bool is_running = TRUE;
	while (is_running) {

        // Handle events:
		get_next_event(&event);
        switch (event.event_type) {

            case (EventType_WIN_CLOSE):
            is_running = FALSE;
            break;

            case (EventType_WIN_RESIZE):
            reload_win(&err);
            if (is_err(&err)) {
                close_graphics();
                warn(&err);
                exit(err.code);
            }
            break;

            case (EventType_KEY_PRESS):
            switch (event.keyboard_key) {
                
                case KeyboardKey_UP:
                break;

                case KeyboardKey_DOWN:
                break;

                case KeyboardKey_LEFT:
                if (current_theme == 0) {
                    current_theme = 7;
                } else {
                    current_theme--;
                }
                break;

                case KeyboardKey_RIGHT:
                if (current_theme == 7) {
                    current_theme = 0;
                } else {
                    current_theme++;
                }
                break;

                case KeyboardKey_SPACE:
				DEBUG_LOG("Time Elapsed Since Last Spacebar Press: %ld ms\n", tick_clock(&clock))
                break;

                case KeyboardKey_NO_KEY:
                case KeyboardKey_UNDEF:
                break;

            }

            default:
            break;

        }

		// Update Free Tiles Position:
		F32 delta_time_secs = ((F32) tick_clock(&clock)) / 1000.0;
		matrix_free.pos_y += delta_time_secs * TILE_DROP_SPD;

        // Drawing:
        set_pad_color(themes[current_theme].color_pad);
        set_bg_color(themes[current_theme].color_bg);
        clear_screen();			// TODO Refactor clear_screen to take pad and bg colors as args
		draw_tile_matrix(themes[current_theme].color_tile_body, themes[current_theme].color_tile_border, &matrix_free,
			&err);
		if (is_err(&err)) {
			warn(&err);
			close_graphics();
			return err.code;
		}

        flip();
	}

    close_graphics();
 
    return ERR_OK;
}
