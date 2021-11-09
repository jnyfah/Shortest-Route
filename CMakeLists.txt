project(Shortest-Route)

cmake_minimum_required(VERSION 3.20.0)

add_executable(${PROJECT_NAME} src/Dijkstra.cpp src/adjacencyList.hpp)

set_target_properties(Shortest-Route PROPERTIES LINK_FLAGS "${linkFlags}")


# TODO: Add tests and install targets if needed.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_options(Shortest-Route PRIVATE /W4)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(Shortest-Route PRIVATE -Wall -Wextra -Wpedantic)
endif()