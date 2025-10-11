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

    GameScreen game_screen;
    init_game_screen(&game_screen);

    init_graphics(&game_screen, DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT, &err);
    if (is_err(&err)) {
        warn(&err);
        return err.code;
    }

    DEBUG_LOG("%s\n", "Start GameScreen data dump")
    DEBUG_LOG("width:                   %d px\n", game_screen.width)
    DEBUG_LOG("height:                  %d px\n", game_screen.height)
    DEBUG_LOG("grid size:               %d px\n", game_screen.grid_sz)
    DEBUG_LOG("horizontal padding:      %d px\n", game_screen.horiz_pad)
    DEBUG_LOG("vertical padding:        %d px\n", game_screen.vert_pad)
    DEBUG_LOG("tile border size:        %d px\n", game_screen.tile_border_sz)
    DEBUG_LOG("%s\n\n", "End GameScreen data dump")

    Color bg;
    init_color(&bg);
    bg.r = 0x00; bg.g = 0xff; bg.b = 0x00;

	Event event;
	while (TRUE) {

        // Handle events:
		get_next_event(&event);
		if (event.event_type == EventType_WIN_CLOSE) {
			break;
		}

        // Drawing:
        clear_screen(&bg);
        flip();
	}

    close_graphics();
 
    return ERR_OK;
}
