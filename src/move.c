#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "rubiks.h"
#include "move.h"

void swap_cubes(Cube* source, Cube* dest) {
    Cube temp = *source;
    *source = *dest;
    *dest = temp;
}

void rotate_main_face(Face* face) {
    // Rotate corners
    swap_cubes(&face->colors[0][0], &face->colors[0][2]);
    swap_cubes(&face->colors[0][0], &face->colors[2][2]);
    swap_cubes(&face->colors[0][0], &face->colors[2][0]);
    // Rotate edges
    swap_cubes(&face->colors[0][1], &face->colors[1][2]);
    swap_cubes(&face->colors[0][1], &face->colors[2][1]);
    swap_cubes(&face->colors[0][1], &face->colors[1][0]);
}


void rotate_front(Face faces[6]) {
    // Rotate the cube to have the front face at the back, then rotate the back
    rotate_cube_y(faces);
    rotate_cube_y(faces);
    rotate_back(faces);
    rotate_cube_y(faces);
    rotate_cube_y(faces);
}

void rotate_right(Face faces[6]) {
    // Rotate the cube to have the right face at the back, then rotate the back
    rotate_cube_y(faces);
    rotate_cube_y(faces);
    rotate_cube_y(faces);
    rotate_back(faces);
    rotate_cube_y(faces);
}

void rotate_left(Face faces[6]) {
    // Rotate the cube to have the left face at the back, then rotate the back
    rotate_cube_y(faces);
    rotate_back(faces);
    rotate_cube_y(faces);
    rotate_cube_y(faces);
    rotate_cube_y(faces);
}

void rotate_up(Face faces[6]) {
    // Rotate the cube to have the upper face at the back, then rotate the back
    rotate_cube_x(faces);
    rotate_back(faces);
    rotate_cube_x(faces);
    rotate_cube_x(faces);
    rotate_cube_x(faces);
}

void rotate_down(Face faces[6]) {
    // Rotate the cube to have the down face at the back, then rotate the back
    rotate_cube_x(faces);
    rotate_cube_x(faces);
    rotate_cube_x(faces);
    rotate_back(faces);
    rotate_cube_x(faces);
}

void rotate_back(Face faces[6]) {
    Cube temp;

    // Rotate top corner
    temp = faces[3].colors[0][0];
    faces[3].colors[0][0] = faces[5].colors[0][2];
    faces[5].colors[0][2] = faces[2].colors[2][2];
    faces[2].colors[2][2] = faces[4].colors[2][0];
    faces[4].colors[2][0] = temp;

    // Rotate middle corner
    temp = faces[3].colors[0][1];
    faces[3].colors[0][1] = faces[5].colors[1][2];
    faces[5].colors[1][2] = faces[2].colors[2][1];
    faces[2].colors[2][1] = faces[4].colors[1][0];
    faces[4].colors[1][0] = temp;

    // Rotate bottom corner
    temp = faces[3].colors[0][2];
    faces[3].colors[0][2] = faces[5].colors[2][2];
    faces[5].colors[2][2] = faces[2].colors[2][0];
    faces[2].colors[2][0] = faces[4].colors[0][0];
    faces[4].colors[0][0] = temp;

    rotate_main_face(&faces[1]);
}

void rotate_cube_x(Face faces[6]) {
    // Same as R, but for the whole cube
    Face temp = faces[3];
    faces[3] = faces[0];
    faces[0] = faces[2];
    faces[2] = faces[1];
    faces[1] = temp;
    rotate_main_face(&faces[1]);
    rotate_main_face(&faces[1]);
    rotate_main_face(&faces[2]);
    rotate_main_face(&faces[2]);
    rotate_main_face(&faces[4]);
    rotate_main_face(&faces[4]);
    rotate_main_face(&faces[4]);
    rotate_main_face(&faces[5]);
}

void rotate_cube_y(Face faces[6]) {
    // Same as U but for the whole cube
    Face temp = faces[0];
    faces[0] = faces[5];
    faces[5] = faces[1];
    faces[1] = faces[4];
    faces[4] = temp;
    rotate_main_face(&faces[3]);
    rotate_main_face(&faces[2]);
    rotate_main_face(&faces[2]);
    rotate_main_face(&faces[2]);
}

void rotate_cube_z(Face faces[6]) {
    // Same as F but for the whole cube
    Face temp = faces[3];
    faces[3] = faces[4];
    faces[4] = faces[2];
    faces[2] = faces[5];
    faces[5] = temp;
    rotate_main_face(&faces[0]);
    rotate_main_face(&faces[1]);
    rotate_main_face(&faces[2]);
    rotate_main_face(&faces[1]);
    rotate_main_face(&faces[1]);
    rotate_main_face(&faces[3]);
    rotate_main_face(&faces[4]);
    rotate_main_face(&faces[5]);
}


void rotate_front_reverse(Face faces[6]) {
    rotate_cube_y(faces);
    rotate_cube_y(faces);
    rotate_back_reverse(faces);
    rotate_cube_y(faces);
    rotate_cube_y(faces);
}

void rotate_right_reverse(Face faces[6]) {
    rotate_cube_y_reverse(faces);
    rotate_back_reverse(faces);
    rotate_cube_y(faces);
}

void rotate_left_reverse(Face faces[6]) {
    rotate_cube_y(faces);
    rotate_back_reverse(faces);
    rotate_cube_y_reverse(faces);
}

void rotate_up_reverse(Face faces[6]) {
    rotate_cube_x(faces);
    rotate_back_reverse(faces);
    rotate_cube_x_reverse(faces);
}

void rotate_down_reverse(Face faces[6]) {
    rotate_cube_x_reverse(faces);
    rotate_back_reverse(faces);
    rotate_cube_x(faces);
}

void rotate_back_reverse(Face faces[6]) {
    rotate_back(faces);
    rotate_back(faces);
    rotate_back(faces);
}

void rotate_cube_x_reverse(Face faces[6]) {
    rotate_cube_x(faces);
    rotate_cube_x(faces);
    rotate_cube_x(faces);
}

void rotate_cube_y_reverse(Face faces[6]) {
    rotate_cube_y(faces);
    rotate_cube_y(faces);
    rotate_cube_y(faces);
}

void rotate_cube_z_reverse(Face faces[6]) {
    rotate_cube_z(faces);
    rotate_cube_z(faces);
    rotate_cube_z(faces);
}
