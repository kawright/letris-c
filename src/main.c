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


    Color bg;
    init_color(&bg);
    bg.r = 0x00; bg.g = 0xff; bg.b = 0x00;

    Color pad;
    init_color(&pad);
    pad.r = 0xff; pad.g = 0x00; pad.b = 0x00;

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
            reload_win();
            break;

            default:
            break;

        }
        clear_event(&event); 

        // Drawing:
        clear_screen(&game_screen, &bg, &pad);
        flip();
	}

    close_graphics();
 
    return ERR_OK;
}
