#pragma once

#include <stdbool.h>
#include "rubiks.h"

void swap_cubes(Color*, Color*);
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

void rotate_front_reverse(Face[6]);
void rotate_back_reverse(Face[6]);
void rotate_down_reverse(Face[6]);
void rotate_left_reverse(Face[6]);
void rotate_right_reverse(Face[6]);
void rotate_up_reverse(Face[6]);
void rotate_cube_x_reverse(Face[6]);
void rotate_cube_y_reverse(Face[6]);
void rotate_cube_z_reverse(Face[6]);
