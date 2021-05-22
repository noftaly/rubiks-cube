#pragma once

#include <stdbool.h>

typedef enum {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    WHITE,
    ORANGE,
    UNSET
} Color;

typedef struct {
    Color color;
} Cube;

typedef struct {
    Cube colors[3][3];
    Color main_color;
} Face;

Face front, back, down, up, left, right;

void create_face(Face*, Color);
void define_cube(Face[6]);
void create_cube(Face[6]);
void reorient_cube(Face[6]);

void display_cube(Face[6]);
void scramble_cube(Face[6]);

void run_move(const char* move, Face[6]);

void solve_cube(Face[6]);
