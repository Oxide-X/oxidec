cmake_minimum_required(VERSION 4.1)

# Project information
project(oxidec
    VERSION 0.0.0
    LANGUAGES CXX
)

# Specify C++ Standard (C++20 recommended for modern features, change to 17 if needed)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# GLOB_RECURSE finds all .cpp files in src/ and its subdirectories
# CONFIGURE_DEPENDS tries to fix the re-run issue (available in CMake 3.12+)
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Create the executable
add_executable(oxidec ${SOURCES})

# Include directories
# This allows you to use #include "driver/index.hpp" or #include "util/ox.consts.hpp"
target_include_directories(oxidec PRIVATE
    src
    include
)

# Enable standard compiler warnings (Good practice)
if(MSVC)
    target_compile_options(oxidec PRIVATE /W4)
else()
    target_compile_options(oxidec PRIVATE -Wall -Wextra -Wpedantic)
endif()
