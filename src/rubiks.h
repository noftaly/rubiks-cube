#pragma once

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

void rotate_front();
void rotate_back();
void rotate_down();
void rotate_left();
void rotate_right();
void rotate_up();
void rotate_cube();

void create_face(Cube matrix[3][3], Color);
void free_face(Cube matrix[3][3]);
void run_move(const char* move);

void define_cube();
void create_cube();
void free_cube();

void display_cube();

void scramble_cube();

void solve_cube();
void make_white_cross();
void place_corners();
void solve_crown();
void make_yellow_cross();
void place_yellow_edges();
void place_yellow_corners();
void solve_yellow_corners();
