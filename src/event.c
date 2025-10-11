/* event.c - event handling */

#include "debug.h"
#include "event.h"
#include "type.h"

#include <SDL2/SDL.h>
#include <stdlib.h>

Void init_event(Event *event) {
    event->event_type = EventType_NO_EVENT;
    event->payload = NULL;
    return;
}

Void get_next_event(Event *event, Err *err) {
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
        DEBUG_LOG("%s\n", "Window close event detected")
        event->event_type = EventType_WIN_CLOSE;
        event->payload = NULL;
        return;


        case SDL_WINDOWEVENT:
        switch (sdl_event.window.event) {
            
            case SDL_WINDOWEVENT_SIZE_CHANGED:
            event->event_type = EventType_WIN_RESIZE;
            EventPayloadWinResize *win_resize_payload = malloc(sizeof(EventPayloadWinResize));
            if (win_resize_payload == NULL) {
                THROW(err, ERR_MEM, "Could not allocate memory for 'EventPayloadWinResize'")
                return;
            }
            win_resize_payload->width     = sdl_event.window.data1;
            win_resize_payload->height    = sdl_event.window.data2;
            event->payload = win_resize_payload;
            DEBUG_LOG("%s\n", "Window resize event detected")
            DEBUG_LOG("New window width: %d\n", win_resize_payload->width)
            DEBUG_LOG("New window height: %d\n", win_resize_payload->height)
            return;

            default:
            DEBUG_LOG("%s\n", "Unsupported window event detected")
            event->event_type = EventType_UNDEF;
            event->payload = NULL;
            return;
        }

        default:
        DEBUG_LOG("%s\n", "Undefined event detected")
        event->event_type = EventType_UNDEF;
        event->payload = NULL;
        return;

    }
    
    return;
}

Void clear_event(Event *event) {
    switch (event->event_type) {

        case EventType_WIN_RESIZE:
        case EventType_KEY_PRESS:
        case EventType_KEY_REL:
        free(event->payload);
        break;

        case EventType_NO_EVENT:
        case EventType_WIN_CLOSE:
        default:
        break;
        
    } 
    event->payload = NULL;
}
