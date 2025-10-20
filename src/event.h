/* event.h - event handling */

#ifndef EVENT_H
#define EVENT_H

#include "err.h"
#include "type.h"

/* ----- ENUMS ----- */

typedef enum ENUM_EVENT_TYPE {
    EventType_NO_EVENT,
    EventType_UNDEF,
    EventType_WIN_CLOSE,
    EventType_WIN_RESIZE,
    EventType_KEY_PRESS,
    EventType_KEY_REL
} EventType;

typedef enum ENUM_KEYBOARD_KEY {
    KeyboardKey_NO_KEY,
    KeyboardKey_UNDEF,
    KeyboardKey_UP,
    KeyboardKey_DOWN,
    KeyboardKey_RIGHT,
    KeyboardKey_LEFT,
    KeyboardKey_SPACE
} KeyboardKey;

/* ----- STRUCTS ----- */

typedef struct STRUCT_EVENT {
    EventType       event_type;
    U16             window_height;
    U16             window_width;
    KeyboardKey     keyboard_key;
} Event;

/* ----- FUNCTIONS ----- */

Void init_event(Event *event);

Void get_next_event(Event *event);

#endif
