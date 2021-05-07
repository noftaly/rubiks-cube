#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rubiks.h"

void swap_cubes(Cube* source, Cube* dest) {
    Cube temp = *source;
    *source = *dest;
    *dest = temp;
}

void facerotate(Cube matrix[3][3]) {
    // Rotate corners
    swap_cubes(&matrix[0][0], &matrix[0][2]);
    swap_cubes(&matrix[0][0], &matrix[2][2]);
    swap_cubes(&matrix[0][0], &matrix[2][0]);
    // Rotate edges
    swap_cubes(&matrix[0][1], &matrix[1][2]);
    swap_cubes(&matrix[0][1], &matrix[2][1]);
    swap_cubes(&matrix[0][1], &matrix[1][0]);
}

void swap_faces(Cube matrix[3][3], char* rc, Cube matrix1[3][3], char* rc1) {
    int cr = *(rc + 1) - '0';
    int cr1 = *(rc1 + 1) - '0';

    if (*rc == 'r') {
        if (*rc1 == 'r') {
            for (int i = 0; i < 3; i++)
                swap_cubes(&matrix[cr][i], &matrix1[cr1][i]);
        } else if (*rc1 == 'c') {
            for (int i = 0; i < 3; i++)
                swap_cubes(&matrix[cr][i], &matrix1[i][cr1]);
        }
    } else if (*rc == 'c') {
        if (*rc1 == 'c') {
            for (int i = 0; i < 3; i++)
                swap_cubes(&matrix[i][cr], &matrix1[i][cr1]);
        } else if (*rc1 == 'r') {
            for (int i = 0; i < 3; i++)
                swap_cubes(&matrix[i][cr], &matrix1[cr1][i]);
        }
    }
}

void rotate_front() {
    swap_cubes(&left.colors[0][2], &left.colors[2][2]);
    swap_cubes(&right.colors[0][0], &right.colors[2][0]);
    swap_faces(down.colors, (char*) "r0", left.colors, (char*) "c2");
    swap_faces(down.colors, (char*) "r0", up.colors, (char*) "r2");
    swap_faces(down.colors, (char*) "r0", right.colors, (char*) "c0");
    facerotate(front.colors);
}

void rotate_right() {
    Cube temp, temp2;

    // Rotate top corner
    temp = up.colors[0][2];
    up.colors[0][2] = front.colors[0][2];
    temp2 = back.colors[2][0];
    back.colors[2][0] = temp;
    temp = down.colors[0][2];
    down.colors[0][2] = temp2;
    front.colors[0][2] = temp;

    // Rotate middle corner
    temp = up.colors[1][2];
    up.colors[1][2] = front.colors[1][2];
    temp2 = back.colors[1][0];
    back.colors[1][0] = temp;
    temp = down.colors[1][2];
    down.colors[1][2] = temp2;
    front.colors[1][2] = temp;

    // Rotate bottom corner
    temp = up.colors[2][2];
    up.colors[2][2] = front.colors[2][2];
    temp2 = back.colors[0][0];
    back.colors[0][0] = temp;
    temp = down.colors[2][2];
    down.colors[2][2] = temp2;
    front.colors[2][2] = temp;

    facerotate(right.colors);
}

void rotate_left() {
    Cube temp, temp2;

    // Rotate top corner
    temp = down.colors[0][0];
    down.colors[0][0] = front.colors[0][0];
    temp2 = back.colors[2][2];
    back.colors[2][2] = temp;
    temp = up.colors[0][0];
    up.colors[0][0] = temp2;
    front.colors[0][0] = temp;

    // Rotate middle corner
    temp = down.colors[1][0];
    down.colors[1][0] = front.colors[1][0];
    temp2 = back.colors[1][2];
    back.colors[1][2] = temp;
    temp = up.colors[1][0];
    up.colors[1][0] = temp2;
    front.colors[1][0] = temp;

    // Rotate bottom corner
    temp = down.colors[2][0];
    down.colors[2][0] = front.colors[2][0];
    temp2 = back.colors[0][2];
    back.colors[0][2] = temp;
    temp = up.colors[2][0];
    up.colors[2][0] = temp2;
    front.colors[2][0] = temp;

    facerotate(left.colors);
}

void rotate_up() {
    Cube temp, temp2;

    // Rotate top corner
    temp = left.colors[0][0];
    left.colors[0][0] = front.colors[0][0];
    temp2 = back.colors[0][0];
    back.colors[0][0] = temp;
    temp = right.colors[0][0];
    right.colors[0][0] = temp2;
    front.colors[0][0] = temp;

    // Rotate middle corner
    temp = left.colors[0][1];
    left.colors[0][1] = front.colors[0][1];
    temp2 = back.colors[0][1];
    back.colors[0][1] = temp;
    temp = right.colors[0][1];
    right.colors[0][1] = temp2;
    front.colors[0][1] = temp;

    // Rotate bottom corner
    temp = left.colors[0][2];
    left.colors[0][2] = front.colors[0][2];
    temp2 = back.colors[0][2];
    back.colors[0][2] = temp;
    temp = right.colors[0][2];
    right.colors[0][2] = temp2;
    front.colors[0][2] = temp;

    facerotate(up.colors);
}

void rotate_down() {
    Cube temp, temp2;

    // Rotate top corner
    temp = right.colors[2][0];
    right.colors[2][0] = front.colors[2][0];
    temp2 = back.colors[2][0];
    back.colors[2][0] = temp;
    temp = left.colors[2][0];
    left.colors[2][0] = temp2;
    front.colors[2][0] = temp;

    // Rotate middle corner
    temp = right.colors[2][1];
    right.colors[2][1] = front.colors[2][1];
    temp2 = back.colors[2][1];
    back.colors[2][1] = temp;
    temp = left.colors[2][1];
    left.colors[2][1] = temp2;
    front.colors[2][1] = temp;

    // Rotate bottom corner
    temp = right.colors[2][2];
    right.colors[2][2] = front.colors[2][2];
    temp2 = back.colors[2][2];
    back.colors[2][2] = temp;
    temp = left.colors[2][2];
    left.colors[2][2] = temp2;
    front.colors[2][2] = temp;

    facerotate(down.colors);
}

void rotate_back() {
    swap_cubes(&up.colors[0][0], &up.colors[0][2]);
    swap_cubes(&down.colors[2][0], &down.colors[2][2]);
    swap_faces(down.colors, (char*) "r2", right.colors, (char*) "c2");
    swap_faces(down.colors, (char*) "r2", up.colors, (char*) "r0");
    swap_faces(down.colors, (char*) "r2", left.colors, (char*) "c0");
    facerotate(back.colors);
}

void create_face(Cube matrix[3][3], Color color) {
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            Cube cube;
            cube.color = color;
            matrix[r][c] = cube;
        }
    }
}

void free_face(Cube matrix[3][3]) {
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c)
            free(&matrix[r][c].color);
    }
}

void run_move(const char* move) {
    for (int i = 0; move[i] != '\0'; ++i) {
        if (move[i + 1] == '\'') {
            switch (move[i]) {
                case 'R': case 'r':
                    rotate_right();
                    rotate_right();
                    rotate_right();
                    break;
                case 'L': case 'l':
                    rotate_left();
                    rotate_left();
                    rotate_left();
                    break;
                case 'U': case 'u':
                    rotate_up();
                    rotate_up();
                    rotate_up();
                    break;
                case 'D': case 'd':
                    rotate_down();
                    rotate_down();
                    rotate_down();
                    break;
                case 'F': case 'f':
                    rotate_front();
                    rotate_front();
                    rotate_front();
                    break;
                case 'B': case 'b':
                    rotate_back();
                    rotate_back();
                    rotate_back();
                    break;
            }
            i++;
        } else {
            switch (move[i]) {
                case 'R': case 'r':
                    rotate_right();
                    break;
                case 'L': case 'l':
                    rotate_left();
                    break;
                case 'U': case 'u':
                    rotate_up();
                    break;
                case 'D': case 'd':
                    rotate_down();
                    break;
                case 'F': case 'f':
                    rotate_front();
                    break;
                case 'B': case 'b':
                    rotate_back();
                    break;
            }
        }
    }
}

void create_cube() {
    create_face(front.colors, GREEN);
    create_face(back.colors, BLUE);
    create_face(down.colors, YELLOW);
    create_face(up.colors, WHITE);
    create_face(left.colors, ORANGE);
    create_face(right.colors, RED);
}

void free_cube() {
    free_face(front.colors);
    free_face(back.colors);
    free_face(down.colors);
    free_face(up.colors);
    free_face(left.colors);
    free_face(right.colors);
}

char* to_char(Color color) {
    switch (color) {
        case GREEN:
            return "\e[0;32mG\e[0m";
        case RED:
            return "\e[0;31mR\e[0m";
        case YELLOW:
            return "\e[0;33mY\e[0m";
        case BLUE:
            return "\e[0;34mB\e[0m";
        case WHITE:
            return "\e[0;37mW\e[0m";
        case ORANGE:
            return "\e[0;95mO\e[0m";
    }
}

void display_cube() {
    printf("          %s  %s  %s\n", to_char(up.colors[0][0].color), to_char(up.colors[0][1].color), to_char(up.colors[0][2].color));
    printf("          %s  %s  %s\n", to_char(up.colors[1][0].color), to_char(up.colors[1][1].color), to_char(up.colors[1][2].color));
    printf("          %s  %s  %s\n", to_char(up.colors[2][0].color), to_char(up.colors[2][1].color), to_char(up.colors[2][2].color));

    printf("%s  %s  %s   %s  %s  %s   %s  %s  %s   %s  %s  %s\n",
        to_char(left.colors[0][0].color), to_char(left.colors[0][1].color), to_char(left.colors[0][2].color),
        to_char(front.colors[0][0].color), to_char(front.colors[0][1].color), to_char(front.colors[0][2].color),
        to_char(right.colors[0][0].color), to_char(right.colors[0][1].color), to_char(right.colors[0][2].color),
        to_char(back.colors[0][0].color), to_char(back.colors[0][1].color), to_char(back.colors[0][2].color)
    );
    printf("%s  %s  %s   %s  %s  %s   %s  %s  %s   %s  %s  %s\n",
        to_char(left.colors[1][0].color), to_char(left.colors[1][1].color), to_char(left.colors[1][2].color),
        to_char(front.colors[1][0].color), to_char(front.colors[1][1].color), to_char(front.colors[1][2].color),
        to_char(right.colors[1][0].color), to_char(right.colors[1][1].color), to_char(right.colors[1][2].color),
        to_char(back.colors[1][0].color), to_char(back.colors[1][1].color), to_char(back.colors[1][2].color)
    );
    printf("%s  %s  %s   %s  %s  %s   %s  %s  %s   %s  %s  %s\n",
        to_char(left.colors[2][0].color), to_char(left.colors[2][1].color), to_char(left.colors[2][2].color),
        to_char(front.colors[2][0].color), to_char(front.colors[2][1].color), to_char(front.colors[2][2].color),
        to_char(right.colors[2][0].color), to_char(right.colors[2][1].color), to_char(right.colors[2][2].color),
        to_char(back.colors[2][0].color), to_char(back.colors[2][1].color), to_char(back.colors[2][2].color)
    );

    printf("          %s  %s  %s\n", to_char(down.colors[0][0].color), to_char(down.colors[0][1].color), to_char(down.colors[0][2].color));
    printf("          %s  %s  %s\n", to_char(down.colors[1][0].color), to_char(down.colors[1][1].color), to_char(down.colors[1][2].color));
    printf("          %s  %s  %s\n", to_char(down.colors[2][0].color), to_char(down.colors[2][1].color), to_char(down.colors[2][2].color));
}

void scramble_cube() {
    char* moves[] = { "U", "U'", "R", "R'", "L", "L'", "D", "D'", "F", "F'", "B", "B'" };
    int total_moves = 12;

    printf("Scramble pattern: ");

    int scramble_time = (rand() % 20) + 10;
    for (int i = 0; i < scramble_time; i++) {
        char* random_move = moves[rand() % total_moves];
        run_move(random_move);
        printf("%s ", random_move);
    }

    printf("\n\n");
}

void make_white_cross() {}
void place_corners() {}
void solve_crown() {}
void make_yellow_cross() {}
void place_yellow_edges() {}
void place_yellow_corners() {}
void solve_yellow_corners() {}

void solve_cube() {
    make_white_cross();
    place_corners();
    solve_crown();
    
    make_yellow_cross();
    place_yellow_edges();
    place_yellow_corners();
    solve_yellow_corners();
}
