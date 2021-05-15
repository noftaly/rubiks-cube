#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
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

    char* name_face[6] = { "up", "down", "right", "left", "front", "back" };

    puts("You will have to enter each color (w,g,o,b,r,y,u) index by index.");
    for (int face = 0; face < 6; face++) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                char color;
                printf("Enter color for cube on face %s at position row=%d,col=%d: ", name_face[face], row+1, col+1);
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
                        cube.color = UNSET;
                        faces[face].colors[row][col] = cube;
                        break;
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
            return "\e[0;90mU\e[0m";
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

bool has_white_cross(Face faces[6]) {
    return faces[3].colors[0][1].color == WHITE
        && faces[3].colors[1][0].color == WHITE
        && faces[3].colors[1][2].color == WHITE
        && faces[3].colors[2][1].color == WHITE
        && faces[3].colors[1][1].color == WHITE;
}

bool has_perfect_white_cross(Face faces[6]) {
    return has_white_cross(faces)
        && faces[0].colors[0][1].color == faces[0].colors[1][1].color
        && faces[1].colors[0][1].color == faces[1].colors[1][1].color
        && faces[4].colors[0][1].color == faces[4].colors[1][1].color
        && faces[5].colors[0][1].color == faces[5].colors[1][1].color;
    ;
}

void make_white_cross(Face faces[6]) {
    int i, j;
    if (faces[3].colors[0][1].color==WHITE
        && faces[3].colors[1][0].color==WHITE
        && faces[3].colors[1][2].color==WHITE
        && faces[3].colors[1][1].color==WHITE
        && faces[3].colors[2][1].color==GREEN
        && faces[0].colors[0][1].color==WHITE
        && faces[0].colors[1][1].color==GREEN
        && faces[5].colors[0][1].color==RED
        && faces[5].colors[1][1].color==RED) {
        run_move("FU'RU",faces);
    }
        if (faces[3].colors[0][1].color==WHITE
        && faces[3].colors[1][0].color==WHITE
        && faces[3].colors[1][2].color==WHITE
        && faces[0].colors[1][1].color==GREEN
        && faces[0].colors[2][1].color==WHITE
        && faces[5].colors[0][1].color==RED
        && faces[5].colors[1][1].color==RED) {
        run_move("F'R'D'RF'F'", faces);
    }
    if (faces[3].colors[0][1].color==WHITE
        && faces[3].colors[1][0].color==WHITE
        && faces[3].colors[1][1].color==WHITE
        && faces[3].colors[1][2].color==WHITE
        && faces[0].colors[1][1].color==GREEN
        && faces[0].colors[1][2].color==WHITE
        && faces[5].colors[0][1].color==RED
        && faces[5].colors[1][1].color==RED
        && faces[5].colors[1][0].color==GREEN) {
        run_move("R'D'RFF",faces);
    }
    if (faces[3].colors[1][1].color==WHITE
        && faces[3].colors[2][1].color==RED
        && faces[0].colors[0][1].color==WHITE
        && faces[0].colors[1][1].color==GREEN
        && faces[5].colors[1][1].color==RED) {
        run_move("FR",faces);
    }
    if (faces[3].colors[1][1].color==WHITE
        && faces[3].colors[1][2].color==ORANGE
        && faces[0].colors[1][1].color==GREEN
        && faces[5].colors[1][1].color==RED
        && faces[5].colors[0][1].color==WHITE) {
        run_move("R'F'U",faces);
    }

}

int get_next_face(int index) {
    switch(index) {
        case 0: return 5;
        case 1: return 4;
        case 4: return 0;
        case 5: return 1;
        default: return -1;
    }
}

int get_previous_face(int index){
    switch(index){
        case 0: return 4;
        case 1: return 5;
        case 4: return 1;
        case 5: return 0;
        default: return -1;
    }
}

void place_corners(Face faces[6]) {
    for (int i = 0; i < 6; i++){
        if  (i == 2 || i == 3) continue;

        int next_face = get_next_face(i);

        Color current_bottom_right = faces[i].colors[2][2].color;
        Color next_main_color = faces[next_face].colors[1][1].color;
        Color next_face_top_right = faces[next_face].colors[0][2].color;
        Color current_main_color = faces[i].colors[1][1].color;

        if ((   current_bottom_right == next_main_color && next_face_top_right == WHITE)
            || (current_bottom_right == WHITE           && next_face_top_right == current_main_color)
            || (current_bottom_right == next_main_color && next_face_top_right == current_main_color)
        )
            run_move("R' D' R D", faces);
        else
            run_move("D", faces);
    }
}



void solve_crown(Face faces[6]) {
    int top_edges[6][2] = {
        { 0, 1 },
        { 2, 1 },
        { -1, -1 }, // Up, no associeted move. Will never be called.
        { -1, -1 }, // Down, same as up.
        { 1, 0 },
        { 1, 2 },
    };

    for (int i = 0; i < 6; i++){
        if  (i == 2 || i == 3) continue;

        int previous_face = get_previous_face(i);
        int next_face = get_next_face(i);

        int associated_top_edge_x = top_edges[i][0];
        int associated_top_edge_y = top_edges[i][1];

        Color top_edge = faces[2].colors[associated_top_edge_x][associated_top_edge_y].color;
        Color previous_face_main_color = faces[previous_face].colors[1][1].color;
        Color current_face_main_color = faces[i].colors[1][1].color;
        Color next_face_main_color = faces[next_face].colors[1][1].color;

        if (faces[i].colors[2][1].color == current_face_main_color) {
            if (top_edge == previous_face_main_color)
                run_move("U' L' U L U F U' F'", faces);
            else if (top_edge == next_face_main_color)
                run_move("U R U' R' U' F' U F", faces);
        } else {
            run_move("D", faces);
        }

        if (faces[i].colors[1][2].color == next_face_main_color && faces[next_face].colors[1][0].color == current_face_main_color)
            run_move("U R U' R' U' F' U F U2 U R U' R' U' F' U F", faces);
    }
}

void make_yellow_cross() {}
void place_yellow_edges() {}
void place_yellow_corners() {}
void solve_yellow_corners() {}

void solve_cube(Face faces[6]) {
    make_white_cross(faces);
    place_corners(faces);
    solve_crown(faces);

    make_yellow_cross();
    place_yellow_edges();
    place_yellow_corners();
    solve_yellow_corners();
}
