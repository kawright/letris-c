/* event.c - event handling */

#include "debug.h"
#include "event.h"
#include "type.h"

#include <SDL2/SDL.h>
#include <stdlib.h>

Void init_event(Event *event) {
    event->event_type               = EventType_NO_EVENT;
    event->window_width             = 0;
    event->window_height            = 0;
    event->keyboard_key             = KeyboardKey_NO_KEY;
    return;
}

Void get_next_event(Event *event) {
    SDL_Event   sdl_event;
    Bool        is_event_available;
    
    is_event_available = SDL_PollEvent(&sdl_event);
    if (!is_event_available) {
        event->event_type           = EventType_NO_EVENT;
        event->window_width         = 0;
        event->window_height        = 0;
        event->keyboard_key         = KeyboardKey_NO_KEY;
        return;
    }

    switch (sdl_event.type) {
        
        case SDL_QUIT:
        DEBUG_LOG("%s\n", "Window close event detected")
        event->event_type           = EventType_WIN_CLOSE;
        event->window_width         = 0;
        event->window_height        = 0;
        event->keyboard_key         = KeyboardKey_NO_KEY;
        return;


        case SDL_WINDOWEVENT:
        switch (sdl_event.window.event) {
            
            case SDL_WINDOWEVENT_SIZE_CHANGED:
            event->event_type       = EventType_WIN_RESIZE;
            event->window_width     = sdl_event.window.data1;
            event->window_height    = sdl_event.window.data2;
            event->keyboard_key     = KeyboardKey_NO_KEY;
            DEBUG_LOG("%s\n", "Window resize event detected")
            DEBUG_LOG("New window width: %d\n", event->window_width)
            DEBUG_LOG("New window height: %d\n", event->window_height)
            return;


            default:
            // DEBUG_LOG("%s\n", "Unsupported window event detected")
            event->event_type           = EventType_UNDEF;
            event->window_width         = 0;
            event->window_height        = 0;
            event->keyboard_key         = KeyboardKey_NO_KEY;
            return;
        }


        case SDL_KEYDOWN:
        event->event_type = EventType_KEY_PRESS;
        switch (sdl_event.key.keysym.sym) {
            
            case SDLK_UP:
            event->window_width         = 0;
            event->window_height        = 0;
            event->keyboard_key         = KeyboardKey_UP;
            DEBUG_LOG("%s\n", "Button Pressed: Up Arrow")
            break;

            case SDLK_DOWN:
            event->window_width         = 0;
            event->window_height        = 0;
            event->keyboard_key         = KeyboardKey_DOWN;
            DEBUG_LOG("%s\n", "Button Pressed: Down Arrow")
            break;
            
            case SDLK_LEFT:
            event->window_width         = 0;
            event->window_height        = 0;
            event->keyboard_key         = KeyboardKey_LEFT;
            DEBUG_LOG("%s\n", "Button Pressed: Left Arrow")
            break;

            case SDLK_RIGHT:
            event->window_width         = 0;
            event->window_height        = 0;
            event->keyboard_key         = KeyboardKey_RIGHT;
            DEBUG_LOG("%s\n", "Button Pressed: Right Arrow")
            break;

            case SDLK_SPACE:
            event->window_width         = 0;
            event->window_height        = 0;
            event->keyboard_key         = KeyboardKey_SPACE;
            DEBUG_LOG("%s\n", "Button Pressed: Space")
            break;

            default:
            event->window_width         = 0;
            event->window_height        = 0;
            event->keyboard_key         = KeyboardKey_UNDEF;
            DEBUG_LOG("%s\n", "Unsupported Key Pressed")
            break;
        }
        return;


        case SDL_KEYUP:
        event->event_type = EventType_KEY_REL;
        switch (sdl_event.key.keysym.sym) {
            
            case SDLK_UP:
            event->window_width         = 0;
            event->window_height        = 0;
            event->keyboard_key         = KeyboardKey_UP;
            DEBUG_LOG("%s\n", "Button Released: Up Arrow")
            break;

            case SDLK_DOWN:
            event->window_width         = 0;
            event->window_height        = 0;
            event->keyboard_key         = KeyboardKey_DOWN;
            DEBUG_LOG("%s\n", "Button Released: Down Arrow")
            break;
            
            case SDLK_LEFT:
            event->window_width         = 0;
            event->window_height        = 0;
            event->keyboard_key         = KeyboardKey_LEFT;
            DEBUG_LOG("%s\n", "Button Released: Left Arrow")
            break;

            case SDLK_RIGHT:
            event->window_width         = 0;
            event->window_height        = 0;
            event->keyboard_key         = KeyboardKey_RIGHT;
            DEBUG_LOG("%s\n", "Button Released: Right Arrow")
            break;

            case SDLK_SPACE:
            event->window_width         = 0;
            event->window_height        = 0;
            event->keyboard_key         = KeyboardKey_SPACE;
            DEBUG_LOG("%s\n", "Button Released: Space")
            break;

            default:
            event->window_width         = 0;
            event->window_height        = 0;
            event->keyboard_key         = KeyboardKey_UNDEF;
            DEBUG_LOG("%s\n", "Unsupported Key Released")
            break;
        }
        return;

        default:
        // DEBUG_LOG("%s\n", "Undefined event detected")
        event->event_type = EventType_UNDEF;
        event->window_width         = 0;
        event->window_height        = 0;
        event->keyboard_key         = KeyboardKey_NO_KEY;
        return;

    }
    
    return;
}
