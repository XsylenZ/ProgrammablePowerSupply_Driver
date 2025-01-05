cmake_minimum_required(VERSION 3.30)
project(programmable-power-supply)

# Define the shared library
add_library(programmable-power-supply SHARED power_supply_library.c)

# Include the header files
target_include_directories(programmable-power-supply PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(programmable-power-supply PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/internal)
