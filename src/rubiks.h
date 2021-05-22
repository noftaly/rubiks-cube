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

void swap_cubes(Cube*, Cube*);
void rotate_main_face(Face*);

void rotate_front(Face[6]);
void rotate_back(Face[6]);
void rotate_down(Face[6]);
void rotate_left(Face[6]);
void rotate_right(Face[6]);
void rotate_up(Face[6]);
void rotate_cube_x(Face[6]);
void rotate_cube_y(Face[6]);
void rotate_cube_z(Face[6]);

void create_face(Face*, Color);
void define_cube(Face[6]);
void create_cube(Face[6]);

void display_cube(Face[6]);
void run_move(const char* move, Face[6]);
void scramble_cube(Face[6]);

bool has_white_cross(Face[6]);
bool has_perfect_white_cross(Face[6]);

void solve_cube();
void make_white_cross(Face[6]);
void place_corners(Face[6]);
void solve_crown(Face[6]);
void make_yellow_cross(Face[6]);
void place_yellow_edges();
void place_yellow_corners();
void solve_yellow_corners();
