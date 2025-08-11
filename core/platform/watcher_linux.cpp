#include <cstdio>
#include <sys/inotify.h>
#include <unistd.h>
#include <sys/stat.h>
#include <filesystem>
#include <map>
#include <poll.h>
#include "watcher_event_types.h"
#include "watcher_core.h"

namespace fastwatch {
    void watch_linux(const std::string& root, bool recursive, std::atomic<bool>& running, WatchCallback callback) {
        int fd = inotify_init1(IN_NONBLOCK);
        if (fd < 0) {
            perror("inotify_init1");
            return;
        }

        std::map<int, std::string> wd_to_path;
        std::function<void(const std::string&)> add_watch = [&](const std::string& path) {
            int wd = inotify_add_watch(fd, path.c_str(), IN_MODIFY | IN_CREATE | IN_DELETE | IN_MOVED_FROM | IN_MOVED_TO);
            if (wd >= 0) wd_to_path[wd] = path;
        };

        if (recursive) {
            for(auto& p : std::filesystem::recursive_directory_iterator(root)) {
                if (p.is_directory()) add_watch(p.path().string());
            }
        } else {
            add_watch(root);
        }

        char buffer[4096];
        while (running) {
            pollfd pfd = {fd, POLLIN, 0};
            int poll_ret = poll(&pfd, 1, 100);
            if (poll_ret <= 0) continue;

            int length = read(fd, buffer, sizeof(buffer));
            if (length <= 0) continue;

            int i = 0;
            while (i < length) {
                auto* event = (struct inotify_event*)&buffer[i];
                std::string base = wd_to_path[event->wd];
                std::string file = event->len ? base + "/" + event->name : base;
                
                if (event->mask & IN_CREATE) {
                    std::string new_path = file;
                    callback(new_path, FASTWATCH_EVENT_CREATED);

                    if (recursive) {
                        struct stat statbuf;
                        if (stat(new_path.c_str(), &statbuf) == 0 && S_ISDIR(statbuf.st_mode)) {
                            add_watch(new_path);
                        }
                    }
                }
                if (event->mask & IN_MODIFY) callback(file, FASTWATCH_EVENT_MODIFIED);
                if (event-> mask & IN_DELETE) callback(file, FASTWATCH_EVENT_DELETED);
                if (event->mask & IN_MOVED_FROM || event->mask & IN_MOVED_TO) callback(file, FASTWATCH_EVENT_MOVED);

                i += sizeof(inotify_event) + event->len;
            }
        }

        for (auto [wd, _] : wd_to_path) inotify_rm_watch(fd, wd);

        close(fd);
    }
}