#pragma once
#include <string>
#include <atomic>
#include <functional>

namespace fastwatch {
    using WatchCallback = std::function<void(const std::string&, const std::string&)>;
    
    void watch_linux(const std::string& path, bool recursive, std::atomic<bool>& running, WatchCallback callback);
}