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
void swap_faces(Cube matrix[3][3], char* rc, Cube matrix1[3][3], char* rc1);
void facerotate(Cube matrix[3][3]);

void rotate_front();
void rotate_back();
void rotate_down();
void rotate_left();
void rotate_right();
void rotate_up();

void create_face(Cube matrix[3][3], Color);
void free_face(Cube matrix[3][3]);
void run_move(const char* move);

void create_cube();
void free_cube();

void display_cube();

void scramble_cube();
