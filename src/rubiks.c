#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rubiks.h"

void swap_cubes(Cube* source, Cube* dest) {
    Cube temp = *source;
    *source = *dest;
    *dest = temp;
}

void rotate_main_face(Cube matrix[3][3]) {
    // Rotate corners
    swap_cubes(&matrix[0][0], &matrix[0][2]);
    swap_cubes(&matrix[0][0], &matrix[2][2]);
    swap_cubes(&matrix[0][0], &matrix[2][0]);
    // Rotate edges
    swap_cubes(&matrix[0][1], &matrix[1][2]);
    swap_cubes(&matrix[0][1], &matrix[2][1]);
    swap_cubes(&matrix[0][1], &matrix[1][0]);
}

void rotate_front(Face faces[6]) {
    Cube temp;

    // Rotate top corner
    temp = faces[3].colors[2][0];
    faces[3].colors[2][0] = faces[4].colors[2][2];
    faces[4].colors[2][2] = faces[2].colors[0][2];
    faces[2].colors[0][2] = faces[5].colors[0][0];
    faces[5].colors[0][0] = temp;

    // Rotate middle corner
    temp = faces[3].colors[2][1];
    faces[3].colors[2][1] = faces[4].colors[1][2];
    faces[4].colors[1][2] = faces[2].colors[0][1];
    faces[2].colors[0][1] = faces[5].colors[1][0];
    faces[5].colors[1][0] = temp;

    // Rotate bottom corner
    temp = faces[3].colors[2][2];
    faces[3].colors[2][2] = faces[4].colors[0][2];
    faces[4].colors[0][2] = faces[2].colors[0][0];
    faces[2].colors[0][0] = faces[5].colors[2][0];
    faces[5].colors[2][0] = temp;

    rotate_main_face(faces[0].colors);
}

void rotate_right(Face faces[6]) {
    Cube temp;

    // Rotate top corner
    temp = faces[3].colors[0][2];
    faces[3].colors[0][2] = faces[0].colors[0][2];
    faces[0].colors[0][2] = faces[2].colors[0][2];
    faces[2].colors[0][2] = faces[1].colors[2][0];
    faces[1].colors[2][0] = temp;

    // Rotate middle corner
    temp = faces[3].colors[1][2];
    faces[3].colors[1][2] = faces[0].colors[1][2];
    faces[0].colors[1][2] = faces[2].colors[1][2];
    faces[2].colors[1][2] = faces[1].colors[1][0];
    faces[1].colors[1][0] = temp;

    // Rotate bottom corner
    temp = faces[3].colors[2][2];
    faces[3].colors[2][2] = faces[0].colors[2][2];
    faces[0].colors[2][2] = faces[2].colors[2][2];
    faces[2].colors[2][2] = faces[1].colors[0][0];
    faces[1].colors[0][0] = temp;

    rotate_main_face(faces[5].colors);
}

void rotate_left(Face faces[6]) {
    Cube temp;

    // Rotate top corner
    temp = faces[2].colors[0][0];
    faces[2].colors[0][0] = faces[0].colors[0][0];
    faces[0].colors[0][0] = faces[3].colors[0][0];
    faces[3].colors[0][0] = faces[1].colors[2][2];
    faces[1].colors[2][2] = temp;

    // Rotate middle corner
    temp = faces[2].colors[1][0];
    faces[2].colors[1][0] = faces[0].colors[1][0];
    faces[0].colors[1][0] = faces[3].colors[1][0];
    faces[3].colors[1][0] = faces[1].colors[1][2];
    faces[1].colors[1][2] = temp;

    // Rotate bottom corner
    temp = faces[2].colors[2][0];
    faces[2].colors[2][0] = faces[0].colors[2][0];
    faces[0].colors[2][0] = faces[3].colors[2][0];
    faces[3].colors[2][0] = faces[1].colors[0][2];
    faces[1].colors[0][2] = temp;

    rotate_main_face(faces[4].colors);
}

void rotate_up(Face faces[6]) {
    Cube temp;

    // Rotate top corner
    temp = faces[4].colors[0][0];
    faces[4].colors[0][0] = faces[0].colors[0][0];
    faces[0].colors[0][0] = faces[5].colors[0][0];
    faces[5].colors[0][0] = faces[1].colors[0][0];
    faces[1].colors[0][0] = temp;

    // Rotate middle corner
    temp = faces[4].colors[0][1];
    faces[4].colors[0][1] = faces[0].colors[0][1];
    faces[0].colors[0][1] = faces[5].colors[0][1];
    faces[5].colors[0][1] = faces[1].colors[0][1];
    faces[1].colors[0][1] = temp;

    // Rotate bottom corner
    temp = faces[4].colors[0][2];
    faces[4].colors[0][2] = faces[0].colors[0][2];
    faces[0].colors[0][2] = faces[5].colors[0][2];
    faces[5].colors[0][2] = faces[1].colors[0][2];
    faces[1].colors[0][2] = temp;

    rotate_main_face(faces[3].colors);
}

void rotate_down(Face faces[6]) {
    Cube temp;

    // Rotate top corner
    temp = faces[5].colors[2][0];
    faces[5].colors[2][0] = faces[0].colors[2][0];
    faces[0].colors[2][0] = faces[4].colors[2][0];
    faces[4].colors[2][0] = faces[1].colors[2][0];
    faces[1].colors[2][0] = temp;

    // Rotate middle corner
    temp = faces[5].colors[2][1];
    faces[5].colors[2][1] = faces[0].colors[2][1];
    faces[0].colors[2][1] = faces[4].colors[2][1];
    faces[4].colors[2][1] = faces[1].colors[2][1];
    faces[1].colors[2][1] = temp;

    // Rotate bottom corner
    temp = faces[5].colors[2][2];
    faces[5].colors[2][2] = faces[0].colors[2][2];
    faces[0].colors[2][2] = faces[4].colors[2][2];
    faces[4].colors[2][2] = faces[1].colors[2][2];
    faces[1].colors[2][2] = temp;

    rotate_main_face(faces[2].colors);
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
    faces[3].colors[0][1] = faces[5].colors[1][0];
    faces[5].colors[1][2] = faces[2].colors[2][1];
    faces[2].colors[2][1] = faces[4].colors[1][0];
    faces[4].colors[1][0] = temp;

    // Rotate bottom corner
    temp = faces[3].colors[0][2];
    faces[3].colors[0][2] = faces[5].colors[2][2];
    faces[5].colors[2][2] = faces[2].colors[2][0];
    faces[2].colors[2][0] = faces[4].colors[0][0];
    faces[4].colors[0][0] = temp;

    rotate_main_face(faces[1].colors);
}

void rotate_cube(Face faces[6]) {
    Face temp = right;
    right = front;
    front = left;
    left = back;
    back = temp;
    rotate_main_face(faces[3].colors);
    rotate_main_face(faces[3].colors);
    rotate_main_face(faces[3].colors);
    rotate_main_face(faces[2].colors);
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

void run_move(const char* move, Face faces[6]) {
    for (int i = 0; move[i] != '\0'; ++i) {
        if (move[i + 1] == '\'') {
            switch (move[i]) {
                case 'R': case 'r':
                    rotate_right(faces);
                    rotate_right(faces);
                    rotate_right(faces);
                    break;
                case 'L': case 'l':
                    rotate_left(faces);
                    rotate_left(faces);
                    rotate_left(faces);
                    break;
                case 'U': case 'u':
                    rotate_up(faces);
                    rotate_up(faces);
                    rotate_up(faces);
                    break;
                case 'D': case 'd':
                    rotate_down(faces);
                    rotate_down(faces);
                    rotate_down(faces);
                    break;
                case 'F': case 'f':
                    rotate_front(faces);
                    rotate_front(faces);
                    rotate_front(faces);
                    break;
                case 'B': case 'b':
                    rotate_back(faces);
                    rotate_back(faces);
                    rotate_back(faces);
                    break;
                case 'Z': case 'z':
                    rotate_cube(faces);
                    rotate_cube(faces);
                    rotate_cube(faces);
                    break;
            }
            i++;
        } else {
            switch (move[i]) {
                case 'R': case 'r':
                    rotate_right(faces);
                    break;
                case 'L': case 'l':
                    rotate_left(faces);
                    break;
                case 'U': case 'u':
                    rotate_up(faces);
                    break;
                case 'D': case 'd':
                    rotate_down(faces);
                    break;
                case 'F': case 'f':
                    rotate_front(faces);
                    break;
                case 'B': case 'b':
                    rotate_back(faces);
                    break;
                case 'Z': case 'z':
                    rotate_cube(faces);
                    break;
            }
        }
    }
}

void create_cube(Face faces[6]) {
    // 0=front, 1=back, 2=down, 3=up, 4=left, 5=right
    create_face(faces[0].colors, GREEN);
    create_face(faces[1].colors, BLUE);
    create_face(faces[2].colors, YELLOW);
    create_face(faces[3].colors, WHITE);
    create_face(faces[4].colors, ORANGE);
    create_face(faces[5].colors, RED);
}

void define_cube(Face faces[6]) {
    create_face(faces[0].colors, UNSET);
    create_face(faces[1].colors, UNSET);
    create_face(faces[2].colors, UNSET);
    create_face(faces[3].colors, UNSET);
    create_face(faces[4].colors, UNSET);
    create_face(faces[5].colors, UNSET);

    puts("You will have to enter each color (w,g,o,b,r,y) index by index.");
    for (int face = 0; face < 6; face++) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                char color;
                printf("Enter color for cube on face %d at position row=%d,col=%d: ", face, row+1, col+1);
                scanf(" %c", &color);
                Cube cube;
                switch (color) {
                    case 'w':
                        cube.color = WHITE;
                        faces[face].colors[row][col] = cube;
                        break;
                    case 'g':
                        cube.color = GREEN;
                        faces[face].colors[row][col] = cube;
                        break;
                    case 'o':
                        cube.color = ORANGE;
                        faces[face].colors[row][col] = cube;
                        break;
                    case 'b':
                        cube.color = BLUE;
                        faces[face].colors[row][col] = cube;
                        break;
                    case 'r':
                        cube.color = RED;
                        faces[face].colors[row][col] = cube;
                        break;
                    case 'y':
                        cube.color = YELLOW;
                        faces[face].colors[row][col] = cube;
                        break;
                    default:
                        puts("Invalid character.");
                        // TODO: Make it try again
                }
            }
        }
    }
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
        case UNSET:
            return "U";
    }
}

void display_cube(Face faces[6]) {
    printf("          %s  %s  %s\n", to_char(faces[3].colors[0][0].color), to_char(faces[3].colors[0][1].color), to_char(faces[3].colors[0][2].color));
    printf("          %s  %s  %s\n", to_char(faces[3].colors[1][0].color), to_char(faces[3].colors[1][1].color), to_char(faces[3].colors[1][2].color));
    printf("          %s  %s  %s\n", to_char(faces[3].colors[2][0].color), to_char(faces[3].colors[2][1].color), to_char(faces[3].colors[2][2].color));

    printf("%s  %s  %s   %s  %s  %s   %s  %s  %s   %s  %s  %s\n",
        to_char(faces[4].colors[0][0].color), to_char(faces[4].colors[0][1].color), to_char(faces[4].colors[0][2].color),
        to_char(faces[0].colors[0][0].color), to_char(faces[0].colors[0][1].color), to_char(faces[0].colors[0][2].color),
        to_char(faces[5].colors[0][0].color), to_char(faces[5].colors[0][1].color), to_char(faces[5].colors[0][2].color),
        to_char(faces[1].colors[0][0].color), to_char(faces[1].colors[0][1].color), to_char(faces[1].colors[0][2].color)
    );
    printf("%s  %s  %s   %s  %s  %s   %s  %s  %s   %s  %s  %s\n",
        to_char(faces[4].colors[1][0].color), to_char(faces[4].colors[1][1].color), to_char(faces[4].colors[1][2].color),
        to_char(faces[0].colors[1][0].color), to_char(faces[0].colors[1][1].color), to_char(faces[0].colors[1][2].color),
        to_char(faces[5].colors[1][0].color), to_char(faces[5].colors[1][1].color), to_char(faces[5].colors[1][2].color),
        to_char(faces[1].colors[1][0].color), to_char(faces[1].colors[1][1].color), to_char(faces[1].colors[1][2].color)
    );
    printf("%s  %s  %s   %s  %s  %s   %s  %s  %s   %s  %s  %s\n",
        to_char(faces[4].colors[2][0].color), to_char(faces[4].colors[2][1].color), to_char(faces[4].colors[2][2].color),
        to_char(faces[0].colors[2][0].color), to_char(faces[0].colors[2][1].color), to_char(faces[0].colors[2][2].color),
        to_char(faces[5].colors[2][0].color), to_char(faces[5].colors[2][1].color), to_char(faces[5].colors[2][2].color),
        to_char(faces[1].colors[2][0].color), to_char(faces[1].colors[2][1].color), to_char(faces[1].colors[2][2].color)
    );

    printf("          %s  %s  %s\n", to_char(faces[2].colors[0][0].color), to_char(faces[2].colors[0][1].color), to_char(faces[2].colors[0][2].color));
    printf("          %s  %s  %s\n", to_char(faces[2].colors[1][0].color), to_char(faces[2].colors[1][1].color), to_char(faces[2].colors[1][2].color));
    printf("          %s  %s  %s\n", to_char(faces[2].colors[2][0].color), to_char(faces[2].colors[2][1].color), to_char(faces[2].colors[2][2].color));
}

void scramble_cube(Face faces[6]) {
    char* moves[] = { "U", "U'", "R", "R'", "L", "L'", "D", "D'", "F", "F'", "B", "B'" };
    int total_moves = 12;

    printf("Scramble pattern: ");

    int scramble_time = (rand() % 20) + 10;
    for (int i = 0; i < scramble_time; i++) {
        char* random_move = moves[rand() % total_moves];
        run_move(random_move, faces);
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
