#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*fastwatch_callback_t)(const char* path, const char* event);
void fastwatch_start(const char* path, int recursive, fastwatch_callback_t cb);
void fastwatch_stop();

#ifdef __cplusplus
}
#endif