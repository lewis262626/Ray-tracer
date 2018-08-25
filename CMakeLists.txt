cmake_minimum_required(VERSION 2.8)

project(ray_tracer)
set(CMAKE_CXX_FLAGS "-Wall -g  -Wextra -Wpedantic -O2")
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

include_directories("${PROJECT_SOURCE_DIR}")

add_executable(ray_tracer ${PROJECT_SOURCE_DIR}/main.cpp)
