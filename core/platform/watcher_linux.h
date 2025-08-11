#pragma once
#include "watcher_core.h"
#include <string>
#include <atomic>
#include <functional>
#include "watcher_event_types.h"

namespace fastwatch {
    using WatchCallback = std::function<void(const std::string&, fastwatch_event_t)>;
    
    void watch_linux(const std::string& path, bool recursive, std::atomic<bool>& running, WatchCallback callback);
}