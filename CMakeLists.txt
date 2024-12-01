# Specify the minimum CMake version
cmake_minimum_required(VERSION 3.15)

# Define the project
project(NesEmulator VERSION 0.1 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set output directories for executables and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)

# Add global include path for config.h
include_directories(${CMAKE_SOURCE_DIR}/include)

# Include the src directory
add_subdirectory(src)

# Enable testing
#add_subdirectory(test)
#enable_testing()
