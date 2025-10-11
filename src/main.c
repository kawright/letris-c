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

    init_graphics(&err);
    if (is_err(&err)) {
        warn(&err);
        return err.code;
    }
   
    Color bg;
    init_color(&bg);
    bg.r = 0x00; bg.g = 0xff; bg.b = 0x00;
    clear_screen(&bg);
    flip();

	Event event;
	while (TRUE) {
		get_next_event(&event);
		if (event.event_type == EventType_WIN_CLOSE) {
			break;
		}
	}

    close_graphics();
 
    return ERR_OK;
}
