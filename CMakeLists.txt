project(Shortest-Route)

cmake_minimum_required(VERSION 3.16)

add_library(${PROJECT_NAME} src/Dijkstra.cpp src/adjacencyList.hpp)

set_target_properties(Shortest-Route PROPERTIES LINK_FLAGS "${linkFlags}")


# set compiler and flags
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_C_COMPILER emcc)
SET(CMAKE_CPP_COMPILER em++)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set( CMAKE_CXX_FLAGS "-s EXPORTED_FUNCTIONS=\"[${exports_string}]\""  )


if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_options(Shortest-Route PRIVATE /W4)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(Shortest-Route PRIVATE -Wall -Wextra -Wpedantic)
endif()



