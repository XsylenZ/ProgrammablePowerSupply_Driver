cmake_minimum_required(VERSION 3.30)
project(KA3305P_example)

# Define the path to the library
set(LIBRARY_PATH ${CMAKE_SOURCE_DIR}/src)

# Find the shared library
link_directories(${LIBRARY_PATH})

# Add the example executable
add_executable(KA3305P_example main.cpp
        ${LIBRARY_PATH}/power_supply_library.c)

# Link the shared library to the example
#target_link_libraries(KA3305P_example programmable-power-supply)

# Include the library headers
#target_include_directories(KA3305P_example PUBLIC ${LIBRARY_PATH})