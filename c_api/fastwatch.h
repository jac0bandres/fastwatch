#pragma once

#include "../core/watcher_event_types.h"
#ifdef __cplusplus
extern "C" {
#endif


typedef void (*fastwatch_callback_t)(const char* path, fastwatch_event_t event);
void fastwatch_watch(const char* path, int recursive, fastwatch_callback_t cb);
void fastwatch_stop();

#ifdef __cplusplus
}
#endif