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

# Header-only library exposed to downstream consumers via add_subdirectory
# or FetchContent. The src/ directory must be on the include path because
# include/profcat/catalog.hpp pulls in src/catalog/*.hpp via relative paths
# and those files in turn re-include "profcat/descriptor.hpp" through the
# main include/ search root.
add_library(profcat INTERFACE)
add_library(profcat::profcat ALIAS profcat)
target_include_directories(profcat INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)
target_compile_features(profcat INTERFACE cxx_std_20)

add_executable(profcat-list src/main.cpp)
target_link_libraries(profcat-list PRIVATE profcat)
target_compile_options(profcat-list PRIVATE
    -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
