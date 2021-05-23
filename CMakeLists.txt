cmake_minimum_required(VERSION 3.19)
project(rubiks_cube C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(rubiks_cube
        src/cube_tester.c
        src/cube_tester.h
        src/main.c
        src/move.c
        src/move.h
        src/rubiks.c
        src/rubiks.h
        src/solve.c
        src/solve.h)
