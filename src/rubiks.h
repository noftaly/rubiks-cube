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
} Face;

Face front, back, down, up, left, right;

void swap_cubes(Cube*, Cube*);
void rotate_main_face(Cube matrix[3][3]);

void rotate_front(Face faces[6]);
void rotate_back(Face faces[6]);
void rotate_down(Face faces[6]);
void rotate_left(Face faces[6]);
void rotate_right(Face faces[6]);
void rotate_up(Face faces[6]);
void rotate_cube(Face faces[6]);

void create_face(Cube matrix[3][3], Color);
void define_cube(Face faces[6]);
void create_cube(Face faces[6]);

void display_cube(Face faces[6]);
void run_move(const char* move, Face face[6]);
void scramble_cube(Face faces[6]);

bool has_white_cross(Face faces[6]);
bool has_perfect_white_cross(Face faces[6]);

void solve_cube();
void make_white_cross(Face faces[6]);
void place_corners(Face faces[6]);
void solve_crown(Face faces[6]);
void make_yellow_cross();
void place_yellow_edges();
void place_yellow_corners();
void solve_yellow_corners();
