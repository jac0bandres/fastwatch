#include "fastwatch.h"
#include "../core/watcher_core.h"

static fastwatch::Watcher* watcher = nullptr;
void fastwatch_start(const char* path, int recursive, fastwatch_callback_t cb) {
    if (watcher) return;

    watcher = new fastwatch::Watcher(
        std::string(path),
        recursive != 0,
        [cb](const std::string& path, const std::string& event) {
            cb(path.c_str(), event.c_str());
        }
    );

    watcher->start();
}

void fastwatch_stop() {
    if (watcher) {
        watcher->stop();
        delete watcher;
        watcher = nullptr;
    }
}