#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    FASTWATCH_EVENT_CREATED = 0,
    FASTWATCH_EVENT_MODIFIED = 1,
    FASTWATCH_EVENT_DELETED = 2,
    FASTWATCH_EVENT_MOVED = 3,
} fastwatch_event_t;

#ifdef __cplusplus
}
#endif
