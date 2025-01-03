cmake_minimum_required(VERSION 3.30)
project(programmable-power-supply C)

set(CMAKE_C_STANDARD 11)

add_library(programmable-power-supply SHARED library.c
        command_ka3000v2.h
        command_kd3300v4.h)
