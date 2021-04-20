#pragma once

typedef enum { RED, BLUE, GREEN, WHITE, YELLOW, ORANGE, UNKNOWN } T_COLOR;
typedef enum { FRONT, BACK, UP, DOWN, RIGHT, LEFT } T_SIDE;

typedef struct {
    T_COLOR color;
} Case;

typedef struct {
    Case grid[3][3];
    T_SIDE side;
} Rubik;

// Rubik* create_rubiks();
void display_cube(Rubik*);
