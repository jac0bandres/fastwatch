cmake_minimum_required(VERSION 3.16)
project(fastwatch)

set(CMAKE_CXX_STANDARD 20)

add_library(fastwatch SHARED
    core/watcher_core.cpp
    core/platform/watcher_linux.cpp
    c_api/fastwatch_c_api.cpp
)
target_include_directories(fastwatch PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core)

target_include_directories(fastwatch PUBLIC
    ${CMAKE_CURRENT_SOURCE}/core
    ${CMAKE_CURRENT_SOURCE}/c_api
)

add_executable(fastwatch_cli cli/main.cpp)
target_link_libraries(fastwatch_cli fastwatch)
target_include_directories(fastwatch_cli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/core)
