#include "watcher_core.h"
#include "platform/watcher_linux.h"
#include <atomic>

namespace fastwatch {
    Watcher::Watcher(const std::string& path, bool recursive, WatchCallback cb)
        : path_(path), recursive_(recursive), callback_(cb), running_(false) {}

    Watcher::~Watcher() {
        stop();
    }

    void Watcher::start() {
        running_ = true;
        watcher_thread_ = std::thread([this]() { watch_loop(); });
    }

    void Watcher::stop() {
        running_ = false;
        if (watcher_thread_.joinable()) watcher_thread_.join();
    }

    void Watcher::watch_loop() {
        watch_linux(path_, recursive_, running_, callback_);
    }

}