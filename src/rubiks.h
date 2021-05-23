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

void create_face(Face*, Color);
void blank_cube(Face[6]);
void define_cube(Face[6]);
void create_cube(Face[6]);
void reorient_cube(Face[6]);

void display_cube(Face[6]);
void scramble_cube(Face[6]);

void display_help();

void run_move(const char* move, Face[6]);

int prompt_stop(Face faces[6], char* move_name);
void solve_cube(Face[6]);
