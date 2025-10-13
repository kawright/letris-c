/* main.c - entry point */

#include "debug.h"
#include "err.h"
#include "event.h"
#include "graph.h"
#include "type.h"

#include <stdio.h>
#include <SDL2/SDL.h>

I16 main(I16 argc, Ch **argv) {

    Err err;
    init_err(&err);

    // Initalize graphics:

    GameScreen game_screen;
    init_game_screen(&game_screen);

    init_graphics(&game_screen, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, &err);
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
   
    Theme theme_classic;                        
    init_theme(&theme_classic, "./asset/font/Caprasimo.ttf");
    theme_classic.color_bg                  = &color_slate_blue;
    theme_classic.color_pad                 = &color_dark_slate_blue;
    theme_classic.color_tile_body           = &color_papaya_whip;
    theme_classic.color_tile_border         = &color_dark_orange;
    theme_classic.color_text_normal         = &color_violet;
    theme_classic.color_text_debug          = &color_white;
   
    Theme theme_red;
    init_theme(&theme_red, "./asset/font/Caprasimo.ttf");
    theme_red.color_bg                      = &color_crimson;
    theme_red.color_pad                     = &color_dark_red;
    theme_red.color_tile_body               = &color_violet;
    theme_red.color_tile_border             = &color_medium_violet_red;
    theme_red.color_text_normal             = &color_papaya_whip;
    theme_red.color_text_debug              = &color_white;  

    game_screen.theme = &theme_red;
    
    init_text(&game_screen, &err);
    if (is_err(&err)) {
        warn(&err);
        SDL_Quit();
        return err.code;
    }

	Event event;
    Bool is_running = TRUE;
	while (is_running) {

        // Handle events:
		get_next_event(&event, &err);
        if (is_err(&err)) {
            close_graphics();
            warn(&err);
            exit(err.code);
        }
        switch (event.event_type) {

            case (EventType_WIN_CLOSE):
            is_running = FALSE;
            break;

            case (EventType_WIN_RESIZE):
            EventPayloadWinResize *win_resize_payload = event.payload;
            set_game_screen(&game_screen, win_resize_payload->width, win_resize_payload->height);
            reload_win(&game_screen, &err);
            if (is_err(&err)) {
                close_graphics();
                warn(&err);
                exit(err.code);
            }
            break;

            default:
            break;

        }
        clear_event(&event); 

        // Drawing:
        clear_screen(&game_screen, &err);
        draw_tile(&game_screen, 2.5, 2.5, "b", &err);
        flip();
	}

    close_graphics();
 
    return ERR_OK;
}
