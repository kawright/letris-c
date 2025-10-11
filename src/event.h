/* event.h - event handling */

#ifndef EVENT_H
#define EVENT_H

#include "type.h"

/* ----- ENUMS ----- */

typedef enum ENUM_EVENT_TYPE {
    EventType_NO_EVENT,
    EventType_UNDEF,
    EventType_WIN_CLOSE,
    EventType_KEY_PRESS,
    EventType_KEY_REL
} EventType;

/* ----- STRUCTS ----- */

typedef struct STRUCT_EVENT {
    EventType       event_type;
    Void            *payload;
} Event;

/* ----- FUNCTIONS ----- */

Void init_event(Event *event);

Void get_next_event(Event *event);

#endif
