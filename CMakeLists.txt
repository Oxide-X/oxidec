cmake_minimum_required(VERSION 4.1)

# Project information
project(oxidec
    VERSION 0.0.0
    LANGUAGES CXX
)

# Specify C++ Standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Generate version header
# Template file: include/version.hpp.in
# Contains:
# #define OXIDEC_VERSION_STRING "@PROJECT_VERSION@"
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/version.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/version.hpp
    @ONLY
)

# Create executable
add_executable(oxidec ${SOURCES})

# Include directories
target_include_directories(oxidec PRIVATE
    src
    include
    ${CMAKE_CURRENT_BINARY_DIR} # Needed for version.hpp
)

# Compiler warnings
if(MSVC)
    target_compile_options(oxidec PRIVATE /W4)
else()
    target_compile_options(oxidec PRIVATE -Wall -Wextra -Wpedantic)
endif()
