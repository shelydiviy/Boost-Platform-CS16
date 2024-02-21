cmake_minimum_required(VERSION 3.10.6)

project(steam_faker)
set(CMAKE_CXX_STANDARD 20)

# Include directories
include_directories(src)
include_directories(public)

# Collect source files
file(GLOB_RECURSE SOURCES src/*.cpp )

# Create the executable
add_executable(steam_faker ${SOURCES})

# Link against the libraries with full paths
target_link_libraries(steam_faker PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/steam_api64.lib
)