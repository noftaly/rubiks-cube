#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "rubiks.h"
#include "move.h"
#include "solve.h"

void create_face(Face* face, Color color) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++)
            face->colors[row][col] = (Cube){ .color = color };
    }
    face->main_color = color;
}

void run_move(const char* move, Face faces[6]) {
    for (int i = 0; move[i] != '\0'; i++) {
        if (move[i + 1] == '\'') {
            switch (move[i]) {
                case 'R': case 'r':
                    rotate_right_reverse(faces);
                    break;
                case 'L': case 'l':
                    rotate_left_reverse(faces);
                    break;
                case 'U': case 'u':
                    rotate_up_reverse(faces);
                    break;
                case 'D': case 'd':
                    rotate_down_reverse(faces);
                    break;
                case 'F': case 'f':
                    rotate_front_reverse(faces);
                    break;
                case 'B': case 'b':
                    rotate_back_reverse(faces);
                    break;
                case 'X': case 'x':
                    rotate_cube_x_reverse(faces);
                    break;
                case 'Y': case 'y':
                    rotate_cube_y_reverse(faces);
                    break;
                case 'Z': case 'z':
                    rotate_cube_z_reverse(faces);
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
                case 'X': case 'x':
                    rotate_cube_x(faces);
                    break;
                case 'Y': case 'y':
                    rotate_cube_y(faces);
                    break;
                case 'Z': case 'z':
                    rotate_cube_z(faces);
                    break;
            }
        }
    }
}

void create_cube(Face faces[6]) {
    // 0=front, 1=back, 2=down, 3=up, 4=left, 5=right
    create_face(&faces[0], GREEN);
    create_face(&faces[1], BLUE);
    create_face(&faces[2], YELLOW);
    create_face(&faces[3], WHITE);
    create_face(&faces[4], ORANGE);
    create_face(&faces[5], RED);
}

void define_cube(Face faces[6]) {
    create_face(&faces[0], UNSET);
    create_face(&faces[1], UNSET);
    create_face(&faces[2], UNSET);
    create_face(&faces[3], UNSET);
    create_face(&faces[4], UNSET);
    create_face(&faces[5], UNSET);

    char* name_face[6] = { "up", "down", "right", "left", "front", "back" };

    puts("You will have to enter each color (w,g,o,b,r,y,u) index by index.");
    for (int face = 0; face < 6; face++) {
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                Color color;
                char input_color;
                printf("Enter color for cube on face  \e[1;33m%s\e[0m  at position row=\e[1;33m%d\e[0m,col=\e[1;33m%d\e[0m: ", name_face[face], row+1, col+1);
                scanf(" %c", &input_color);
                switch (input_color) {
                    case 'w': case 'W': color = WHITE; break;
                    case 'g': case 'G': color = GREEN; break;
                    case 'o': case 'O': color = ORANGE; break;
                    case 'b': case 'B': color = BLUE; break;
                    case 'r': case 'R': color = RED; break;
                    case 'y': case 'Y': color = YELLOW; break;
                    default: color = UNSET; break;
                }
                faces[face].colors[row][col] = (Cube){ .color = color };
                if (row == col == 1)
                    faces[face].main_color = color;
            }
        }
    }
}

char* to_char(Color color) {
    switch (color) {
        case GREEN:  return "\e[0;32mG\e[0m";
        case RED:    return "\e[0;31mR\e[0m";
        case YELLOW: return "\e[0;33mY\e[0m";
        case BLUE:   return "\e[0;34mB\e[0m";
        case WHITE:  return "\e[0;37mW\e[0m";
        case ORANGE: return "\e[0;95mO\e[0m";
        default:     return "\e[0;90mU\e[0m"; // Grey
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

    // Random number between 10 and 29
    int scramble_time = (rand() % 20) + 10;
    for (int i = 0; i < scramble_time; i++) {
        char* random_move = moves[rand() % total_moves];
        run_move(random_move, faces);
        printf("%s ", random_move);
    }

    printf("\n\n");
}

void reorient_cube(Face faces[6]) {
    switch (faces[0].main_color) {
        case BLUE:
            run_move("Y Y", faces);
            return;
        case ORANGE:
            run_move("Y", faces);
            return;
        case RED:
            run_move("Y'", faces);
            return;
        default:
            return;
    }
}

void solve_cube(Face faces[6]) {
    make_perfect_white_cross(faces);
    place_white_corners(faces);
    solve_crown(faces);

    make_yellow_cross(faces);
    place_yellow_edges(faces);
    reorient_cube(faces);
    place_yellow_corners(faces);
    reorient_cube(faces);
    solve_yellow_corners();
}
