#pragma once

#include <string>
#include <functional>
#include <thread>
#include <atomic>
#include "./watcher_event_types.h"

namespace fastwatch {
    using WatchCallback = std::function<void(const std::string& path, fastwatch_event_t event)>;

    class Watcher {
        public:
        Watcher(const std::string& path, bool recursive, WatchCallback callback);
        ~Watcher();

        void start();
        void stop();

        private:
        std::string path_;
        bool recursive_;
        WatchCallback callback_;
        std::atomic<bool> running_;
        std::thread watcher_thread_;

        void watch_loop(); // platform specific
    };
}