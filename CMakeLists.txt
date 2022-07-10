project(Shortest-Route)

cmake_minimum_required(VERSION 3.14)

add_library(${PROJECT_NAME} src/Dijkstra.cpp src/adjacencyList.hpp)

set_target_properties(Shortest-Route PROPERTIES LINK_FLAGS "${linkFlags}")


# set compiler and flags
set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_C_COMPILER emcc)
SET(CMAKE_CPP_COMPILER em++)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build.emscripten)

if(MSVC)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
else(MSVC)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
endif(MSVC)


if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_options(Shortest-Route PRIVATE /W4)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_options(Shortest-Route PRIVATE -Wall -Wextra -Wpedantic)
endif()


set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


file(GLOB_RECURSE CORE_SRC src/*.cpp)
add_executable(index ${CORE_SRC})

set_target_properties(index PROPERTIES LINK_FLAGS "-s NO_DISABLE_EXCEPTION_CATCHING  --std=c++1z --preload-file ${CMAKE_SOURCE_DIR}/utils --bind")



