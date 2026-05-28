cmake_minimum_required(VERSION 3.20)
project(profiler-catalog
        VERSION 0.1.0
        DESCRIPTION "Constexpr catalog of GPU profiler metrics"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(profcat-list src/main.cpp)
target_include_directories(profcat-list PRIVATE include)
target_compile_options(profcat-list PRIVATE
    -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
