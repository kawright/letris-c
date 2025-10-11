/* event.c - event handling */

#include "event.h"
#include "type.h"

#include <SDL2/SDL.h>

Void init_event(Event *event) {
    event->event_type = EventType_NO_EVENT;
    event->payload = NULL;
    return;
}

Void get_next_event(Event *event) {
    SDL_Event   sdl_event;
    Bool        is_event_available;
    
    is_event_available = SDL_PollEvent(&sdl_event);
    if (!is_event_available) {
        event->event_type = EventType_NO_EVENT;
        event->payload = NULL;
        return;
    }

    switch (sdl_event.type) {
        
        case SDL_QUIT:
        event->event_type = EventType_WIN_CLOSE;
        event->payload = NULL;
        return;

        default:
        event->event_type = EventType_UNDEF;
        event->payload = NULL;
        return;

    }
    
    return;
}

