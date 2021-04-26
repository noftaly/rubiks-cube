cmake_minimum_required(VERSION 3.19)
project(rubiks_cube C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(rubiks_cube
        src/main.c
        src/rubiks.c
        src/rubiks.h)
