#include <iostream>
#include <chrono>
#include <thread>
#include "watcher_core.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: fastwatch_cli <path_to_watch>\n";
        return 1;
    }

    fastwatch::Watcher watcher(argv[1], true,
    [](const std::string& path, const std::string& event) {
        std::cout << "Event:" << event << " on " << path << std::endl;
    });

    watcher.start();

    std::cout << "Watching " << argv[1] << " recursively.";

    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    watcher.stop();

    return 0;
}