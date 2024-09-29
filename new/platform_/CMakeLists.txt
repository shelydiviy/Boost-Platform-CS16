cmake_minimum_required(VERSION 3.10.6)

project(platform)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")

# Include directories
include_directories(src)
include_directories(public)

# Collect source files
file(GLOB_RECURSE SOURCES src/*.cpp src/data_parser.cpp)

# Create the executable
add_executable(platform ${SOURCES})

# Link against the libraries with full paths
target_link_libraries(platform PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/lib/linux32/libsteam_api.so
)