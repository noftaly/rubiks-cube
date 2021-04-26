#pragma once

void strswap(char* s,char* t);
void strarrswap(char* matrix[3][3], char* rc, char* matrix1[3][3], char* rc1);
void facerotate(char* matrix[3][3]);
void rfacerotate(char* matrix[3][3]);

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

void create_face(char* matrix[3][3], char* color);
void free_face(char* matrix[3][3]);
void run_move(const char* move);

void create_cube();
void free_cube();

void display_cube();

typedef struct {
    char* color[3][3];
} Face;

Face front, back, down, up, left, right;
