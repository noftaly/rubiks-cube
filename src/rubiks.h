#pragma once

typedef enum {
    RED,
    GREEN,
    BLUE,
    YELLOW,
    WHITE,
    ORANGE
} Color;

typedef struct {
    Color color;
} Cube;

typedef struct {
    Cube colors[3][3];
} Face;

Face front, back, down, up, left, right;

void swap_cubes(Cube*, Cube*);
void strarrswap(Cube matrix[3][3], char* rc, Cube matrix1[3][3], char* rc1);
void facerotate(Cube matrix[3][3]);
void rfacerotate(Cube matrix[3][3]);

void rotate_front();
void rotate_back();
void rotate_down();
void rotate_left();
void rotate_right();
void rotate_up();

void rotate_front_reverse();
void rotate_back_reverse();
void rotate_down_reverse();
void rotate_left_reverse();
void rotate_right_reverse();
void rotate_up_reverse();

void create_face(Cube matrix[3][3], Color);
void free_face(Cube matrix[3][3]);
void run_move(const char* move);

void create_cube();
void free_cube();

void display_cube();
