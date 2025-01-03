cmake_minimum_required(VERSION 3.30)
project(Programmable_Power_Supply C)

set(CMAKE_C_STANDARD 11)

add_library(Programmable_Power_Supply SHARED library.c
        command_ka3000v2.h
        cmake-build-debug/command_kd3305p.h)
