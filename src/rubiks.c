#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rubiks.h"

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

bool has_white_cross(Face faces[6]) {
    return faces[3].colors[0][1].color == WHITE
        && faces[3].colors[1][0].color == WHITE
        && faces[3].colors[1][2].color == WHITE
        && faces[3].colors[2][1].color == WHITE
        && faces[3].main_color == WHITE;
}

bool has_perfect_white_cross(Face faces[6]) {
    return has_white_cross(faces)
        && faces[0].colors[0][1].color == faces[0].main_color
        && faces[1].colors[0][1].color == faces[1].main_color
        && faces[4].colors[0][1].color == faces[4].main_color
        && faces[5].colors[0][1].color == faces[5].main_color;
    ;
}

void make_white_cross(Face faces[6]) {
    if (faces[3].colors[0][1].color == WHITE
        && faces[3].colors[1][0].color == WHITE
        && faces[3].colors[1][2].color == WHITE
        && faces[3].main_color == WHITE
        && faces[3].colors[2][1].color == GREEN
        && faces[0].colors[0][1].color == WHITE
        && faces[0].main_color == GREEN
        && faces[5].colors[0][1].color == RED
        && faces[5].main_color == RED)
        run_move("F U' R U", faces);

    if (faces[3].colors[0][1].color == WHITE
        && faces[3].colors[1][0].color == WHITE
        && faces[3].colors[1][2].color == WHITE
        && faces[0].main_color == GREEN
        && faces[0].colors[2][1].color == WHITE
        && faces[5].colors[0][1].color == RED
        && faces[5].main_color == RED)
        run_move("F' R' D' R F F", faces);

    if (faces[3].colors[0][1].color == WHITE
        && faces[3].colors[1][0].color == WHITE
        && faces[3].main_color == WHITE
        && faces[3].colors[1][2].color == WHITE
        && faces[0].main_color == GREEN
        && faces[0].colors[1][2].color == WHITE
        && faces[5].colors[0][1].color == RED
        && faces[5].main_color == RED
        && faces[5].colors[1][0].color == GREEN)
        run_move("R' D' R F F", faces);

    if (faces[3].main_color == WHITE
        && faces[3].colors[2][1].color == RED
        && faces[0].colors[0][1].color == WHITE
        && faces[0].main_color == GREEN
        && faces[5].main_color == RED)
        run_move("F R", faces);

    if (faces[3].main_color == WHITE
        && faces[3].colors[1][2].color == ORANGE
        && faces[0].main_color == GREEN
        && faces[5].main_color == RED
        && faces[5].colors[0][1].color == WHITE)
        run_move("R' F' U", faces);
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
    switch(index) {
        case 0: return 4;
        case 1: return 5;
        case 4: return 1;
        case 5: return 0;
        default: return -1;
    }
}

void place_corners(Face faces[6]) {
/*
    for (int j=0; j<6; j++){
        for (int i = 0; i < 6; i++) {
            if (i == 2 || i == 3) continue;

            int next_face = get_next_face(i);

            Color current_bottom_right = faces[i].colors[2][2].color;
            Color next_main_color = faces[next_face].colors[1][1].color;
            Color next_face_top_right = faces[next_face].colors[0][2].color;
            Color current_main_color = faces[i].colors[1][1].color;

            if ((   current_bottom_right == next_main_color && next_face_top_right == WHITE)
                || (current_bottom_right == WHITE           && next_face_top_right == current_main_color)
                || (current_bottom_right == next_main_color && next_face_top_right == current_main_color)){
                printf("Ca marche: %d", i);
                run_move("R' D' R D", faces);*/
/*        while (faces[3].colors[0][0].color!=WHITE || faces[3].colors[0][1].color!=WHITE || faces[3].colors[0][2].color!=WHITE 
            || faces[3].colors[1][0].color!=WHITE || faces[3].colors[1][1].color!=WHITE || faces[3].colors[1][2].color!=WHITE 
            || faces[3].colors[2][0].color!=WHITE || faces[3].colors[2][1].color!=WHITE || faces[3].colors[2][2].color!=WHITE){*/

    if ((   faces[0].colors[2][2].color == faces[5].colors[1][1].color && faces[5].colors[2][0].color == WHITE && faces[2].colors[0][2].color==faces[0].colors[1][1].color)
        || (faces[0].colors[2][2].color == WHITE           && faces[5].colors[2][0].color == faces[0].colors[1][1].color && faces[2].colors[0][2].color==faces[5].colors[1][1].color)
        || (faces[0].colors[2][2].color == faces[5].colors[1][1].color && faces[5].colors[2][0].color == faces[0].colors[1][1].color && faces[2].colors[0][2].color==WHITE)){
        //||(faces[0].colors[2][2].color == )){// green and red faces
        run_move("R' D' R D", faces);
        printf("A");
    }
            
    if ((   faces[5].colors[2][2].color == faces[1].colors[1][1].color && faces[1].colors[2][0].color == WHITE && faces[2].colors[2][2].color==faces[5].colors[1][1].color)
        || (faces[5].colors[2][2].color == WHITE  && faces[1].colors[2][0].color == faces[5].colors[1][1].color && faces[2].colors[2][2].color==faces[1].colors[1][1].color)
        || (faces[5].colors[2][2].color == faces[1].colors[1][1].color && faces[1].colors[2][0].color == faces[5].colors[1][1].color && faces[2].colors[2][2].color==WHITE)){//red and blue faces
        run_move("B' D' B D", faces);
        printf("B");
    }

    if ((   faces[1].colors[2][2].color == faces[4].colors[1][1].color && faces[4].colors[2][0].color == WHITE && faces[2].colors[2][0].color==faces[1].colors[1][1].color)
        || (faces[1].colors[2][2].color == WHITE           && faces[4].colors[2][0].color == faces[1].colors[1][1].color && faces[2].colors[2][0].color==faces[4].colors[1][1].color)
        || (faces[1].colors[2][2].color == faces[4].colors[1][1].color && faces[4].colors[2][0].color == faces[1].colors[1][1].color && faces[2].colors[2][0].color==WHITE)){//blue and orange faces
        run_move("L' D' L D", faces);
        printf("C");
    }

    if ((   faces[4].colors[2][2].color == faces[0].colors[1][1].color && faces[0].colors[2][0].color == WHITE && faces[2].colors[0][0].color==faces[4].colors[1][1].color)
        || (faces[4].colors[2][2].color == WHITE           && faces[0].colors[2][0].color == faces[4].colors[1][1].color && faces[2].colors[0][0].color==faces[0].colors[1][1].color)
        || (faces[4].colors[2][2].color == faces[0].colors[1][1].color && faces[0].colors[2][0].color == faces[4].colors[1][1].color && faces[2].colors[0][0].color==WHITE)){//orange and green faces
        run_move("F' D' F D", faces);
        printf("D");
    }
                
    if((faces[3].colors[0][0].color!=WHITE || faces[3].colors[0][1].color!=WHITE || faces[3].colors[0][2].color!=WHITE 
    || faces[3].colors[1][0].color!=WHITE || faces[3].colors[1][1].color!=WHITE || faces[3].colors[1][2].color!=WHITE 
    || faces[3].colors[2][0].color!=WHITE || faces[3].colors[2][1].color!=WHITE || faces[3].colors[2][2].color!=WHITE)){
        run_move("D", faces);
        printf("E"); //Boucle infini

    //    place_corners(faces);
    }

}
        
    
/*
        }
        int next_face = get_next_face(j);

        Color current_bottom_right = faces[j].colors[2][2].color;
        Color next_main_color = faces[next_face].colors[1][1].color;
        Color next_face_top_right = faces[next_face].colors[0][2].color;
        Color current_main_color = faces[j].colors[1][1].color;


        if ((   current_bottom_right == next_main_color && next_face_top_right == WHITE)
            || (current_bottom_right == WHITE           && next_face_top_right == current_main_color)
            || (current_bottom_right == next_main_color && next_face_top_right == current_main_color)){
                printf("HIII");
                run_move("U", faces);
        }
    }
}*/



void solve_crown(Face faces[6]) {
    int top_edges[6][2] = {
        { 0, 1 },
        { 2, 1 },
        { -1, -1 }, // Up, no associeted move. Will never be called.
        { -1, -1 }, // Down, same as up.
        { 1, 0 },
        { 1, 2 },
    };

    for (int i = 0; i < 6; i++) {
        if (i == 2 || i == 3) continue;

        int previous_face = get_previous_face(i);
        int next_face = get_next_face(i);

        int associated_top_edge_x = top_edges[i][0];
        int associated_top_edge_y = top_edges[i][1];

        Color top_edge = faces[2].colors[associated_top_edge_x][associated_top_edge_y].color;
        Color previous_face_main_color = faces[previous_face].main_color;
        Color current_face_main_color = faces[i].main_color;
        Color next_face_main_color = faces[next_face].main_color;

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

void make_yellow_cross(Face faces[6]) {

//    while(faces[2].colors[0][1].color !=YELLOW && faces[2].colors[1][0].color !=YELLOW && faces[2].colors[1][1].color !=YELLOW 
//            && faces[2].colors[1][2].color !=YELLOW && faces[2].colors[2][1].color !=YELLOW){


        if (faces[2].colors[1][1].color== YELLOW && faces[2].colors[0][1].color==YELLOW && faces[2].colors[1][0].color==YELLOW 
        || faces[2].colors[1][1].color==YELLOW && faces[2].colors[0][1].color==YELLOW && faces[2].colors[1][2].color==YELLOW
        || faces[2].colors[1][1].color==YELLOW && faces[2].colors[1][0].color==YELLOW && faces[2].colors[2][1].color==YELLOW
        || faces[2].colors[1][1].color==YELLOW && faces[2].colors[1][2].color==YELLOW && faces[2].colors[2][1].color==YELLOW){//case of yellow L
            run_move(" Z Z R' U' F' U F R Z Z", faces);
        }

        else if ((faces[2].colors[1][0].color==YELLOW && faces[2].colors[1][1].color==YELLOW && faces[2].colors[1][2].color==YELLOW) 
        || (faces[2].colors[0][1].color==YELLOW && faces[2].colors[1][1].color==YELLOW && faces[2].colors[2][1].color==YELLOW)){//case of the yellow line
            printf("If du LINE");
            run_move("Z Z F R U R' U' F'Z Z", faces);
        }

        else if (faces[2].colors[1][1].color==YELLOW){ //case of 1 point
            run_move("Z Z R' U' F' U F R F R U R' U' F' Z Z", faces);
            if (faces[2].colors[0][1].color!= YELLOW && faces[2].colors[1][0].color!= YELLOW || faces[2].colors[1][1].color //we verify
                != YELLOW || faces[2].colors[1][2].color!= YELLOW || faces[2].colors[2][1].color!=YELLOW){
                    make_yellow_cross(faces);
            }
        }
}


void place_yellow_edges() {}
    /*while (faces[0].colors[2][1].color!=faces[0].colors[1][1].color 
        && faces[1].colors[2][1].color!=faces[0].colors[1][1].color){
            rotate_cube_y(faces);
            run_move("U", faces);
    }

        if (faces[2].colors[0][1].color==YELLOW && faces[2].colors[1][0].color==YELLOW && faces[2].colors[1][1].color==YELLOW 
        && faces[2].colors[1][2].color==YELLOW && faces[2].colors[2][1].color==YELLOW 
        && faces[1].colors[2][1].color==faces[1].colors[1][1].color && faces[4].colors[2][1].color==faces[4].colors[1][1].color) {
            run_move("Z Z R U U R' U' R U' R' U' Z Z", faces);
    }

                || (faces[1].colors[2][1].color==faces[1].colors[1][1].color && faces[4].colors[2][1].color==faces[4].colors[1][1].color)
                || (faces[5].colors[2][1].color==faces[5].colors[1][1].color && faces[0].colors[2][1].color==faces[0].colors[1][1].color))){

    
    if (faces[2].colors[0][1].color==YELLOW && faces[2].colors[1][0].color==YELLOW && faces[2].colors[1][1].color==YELLOW 
        && faces[2].colors[1][2].color==YELLOW && faces[2].colors[2][1].color==YELLOW
        && ((faces[0].colors[2][1].color==faces[0].colors[1][1].color && faces[1].colors[2][1].color==faces[1].colors[1][1].color) 
            || (faces[4].colors[2][1].color==faces[4].colors[1][1].color && faces[5].colors[2][1].color==faces[5].colors[1][1].color)){
            run_move("Z Z R U U R' U' R U' R' Z Z", faces);            
    }
    
}*/
void place_yellow_corners() {}
void solve_yellow_corners() {}

void solve_cube(Face faces[6]) {
    make_white_cross(faces);
    place_corners(faces);
    solve_crown(faces);

    make_yellow_cross(faces);
    place_yellow_edges();
    place_yellow_corners();
    solve_yellow_corners();
}
