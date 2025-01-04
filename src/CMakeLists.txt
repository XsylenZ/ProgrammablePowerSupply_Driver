cmake_minimum_required(VERSION 3.30)
project(programmable-power-supply)

# Define the shared library
add_library(programmable-power-supply SHARED library.c
        internal/command_ka3000v2.c
        internal/command_kd3300v4.c)

# Include the header files
target_include_directories(programmable-power-supply PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(programmable-power-supply PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/internal)