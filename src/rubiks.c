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

Color ask_color(Face faces[6], int row, int col, int color_counter[9]) {
    int clr = 0;
    printf("\e[0;90m> ");
    int scan_result = scanf("%d", &clr);
    printf("\e[0m");
    getchar();
    while (!scan_result || clr < 0 || clr > 6){
        puts("\e[0;31mInvalid color.\e[0m Please retry:");
        return ask_color(faces, row, col, color_counter);
    }
    if (clr == 6)
        return clr;
    while (color_counter[clr] <= 0){
        puts("\e[0;31mInvalid color.\e[0m Maximum frequency reached. Please retry:");
        return ask_color(faces, row, col, color_counter);
    }
    if (row == 1 && col == 1){
        for (int i = 0; i < 6; i++) {
            while (faces[i].colors[row][col].color == clr) {
                puts("\e[0;31mInvalid color.\e[0m Already center of another face. Please retry:");
                return ask_color(faces, row, col, color_counter);
            }
        }
    }
    return clr;
}

void define_cube(Face faces[6]) {
    for (int i = 0; i < 6; i++)
        create_face(&faces[i], UNSET);

    char* name_face[6] = { "up", "down", "right", "left", "front", "back" };
    int color_counter[] = { 9, 9, 9, 9, 9, 9 };
    while (true) {
        // 1. Enter face
        puts("Enter face number: \e[1;34m0\e[0m=\e[1;34mfront\e[0m | \e[1;34m1\e[0m=\e[1;34mback\e[0m | \e[1;34m2\e[0m=\e[1;34mbottom\e[0m | \e[1;34m3\e[0m=\e[1;34mtop\e[0m | \e[1;34m4\e[0m=\e[1;34mleft\e[0m | \e[1;34m5\e[0m=\e[1;34mright\e[0m | \e[1;34m-1\e[0m to \e[1;34mquit\e[0m.");
        int scan_result;
        int face_index = 0;
        printf("\e[0;90m> ");
        scan_result = scanf("%d", &face_index);
        printf("\e[0m");
        getchar();

        if (face_index == -1)
            break;
        while (!scan_result || face_index < 0 || face_index > 5){
            puts("\e[0;31mInvalid face.\e[0m Please retry:");
            scan_result = scanf("%d", &face_index);
        }

        // 2. Enter coordinates
        puts("Enter \e[4;37mcube's coordinates\e[0m separated by a space. First the row, then the column: they are both comprised between 0 and 2 included. For example: '1 1' for the middle.");
        int row = 0, col = 0;
        printf("\e[0;90m> ");
        scan_result = scanf("%d %d", &row, &col);
        printf("\e[0m");
        getchar();

        while (!scan_result || row < 0 || row > 2 || col < 0 || col > 2){
            puts("\e[0;31mInvalid coordinates.\e[0m Please retry:");
            scan_result = scanf("%d %d", &row, &col);
        }

        // 3. Enter color
        puts("Enter color: \e[1;37m0\e[0m=\e[1;31mred\e[0;90m | \e[1;37m1\e[0m=\e[1;32mgreen\e[0;90m | \e[1;37m2\e[0m=\e[1;34mblue\e[0;90m | \e[1;37m3\e[0m=\e[1;33myellow\e[0;90m | \e[1;37m4\e[0m=\e[1;37mwhite\e[0;90m | \e[1;37m5\e[0m=\e[1;91morange\e[0m | \e[1;37m6\e[0m=\e[1;90munset\e[0m");
        Color clr = ask_color(faces, row, col, color_counter);

        // 4. Act accordinly
        color_counter[clr]--;
        faces[face_index].colors[row][col].color = clr;
        if (row == 1 && col == 1)
            faces[face_index].main_color = clr;
    }
}

char* to_char(Color color) {
    switch (color) {
        case GREEN:  return "\e[0;32mG\e[0m";
        case RED:    return "\e[0;31mR\e[0m";
        case YELLOW: return "\e[0;33mY\e[0m";
        case BLUE:   return "\e[0;34mB\e[0m";
        case WHITE:  return "\e[0;37mW\e[0m";
        case ORANGE: return "\e[0;91mO\e[0m";
        default:     return "\e[0;90mU\e[0m"; // Grey
    }
}

void display_cube(Face faces[6]) {
    printf("          %s  %s  %s\n", to_char(faces[3].colors[0][0].color), to_char(faces[3].colors[0][1].color), to_char(faces[3].colors[0][2].color));
    printf("          %s  %s  %s\n", to_char(faces[3].colors[1][0].color), to_char(faces[3].main_color), to_char(faces[3].colors[1][2].color));
    printf("          %s  %s  %s\n", to_char(faces[3].colors[2][0].color), to_char(faces[3].colors[2][1].color), to_char(faces[3].colors[2][2].color));

    printf("%s  %s  %s   %s  %s  %s   %s  %s  %s   %s  %s  %s\n",
        to_char(faces[4].colors[0][0].color), to_char(faces[4].colors[0][1].color), to_char(faces[4].colors[0][2].color),
        to_char(faces[0].colors[0][0].color), to_char(faces[0].colors[0][1].color), to_char(faces[0].colors[0][2].color),
        to_char(faces[5].colors[0][0].color), to_char(faces[5].colors[0][1].color), to_char(faces[5].colors[0][2].color),
        to_char(faces[1].colors[0][0].color), to_char(faces[1].colors[0][1].color), to_char(faces[1].colors[0][2].color)
    );
    printf("%s  %s  %s   %s  %s  %s   %s  %s  %s   %s  %s  %s\n",
        to_char(faces[4].colors[1][0].color), to_char(faces[4].main_color), to_char(faces[4].colors[1][2].color),
        to_char(faces[0].colors[1][0].color), to_char(faces[0].main_color), to_char(faces[0].colors[1][2].color),
        to_char(faces[5].colors[1][0].color), to_char(faces[5].main_color), to_char(faces[5].colors[1][2].color),
        to_char(faces[1].colors[1][0].color), to_char(faces[1].main_color), to_char(faces[1].colors[1][2].color)
    );
    printf("%s  %s  %s   %s  %s  %s   %s  %s  %s   %s  %s  %s\n",
        to_char(faces[4].colors[2][0].color), to_char(faces[4].colors[2][1].color), to_char(faces[4].colors[2][2].color),
        to_char(faces[0].colors[2][0].color), to_char(faces[0].colors[2][1].color), to_char(faces[0].colors[2][2].color),
        to_char(faces[5].colors[2][0].color), to_char(faces[5].colors[2][1].color), to_char(faces[5].colors[2][2].color),
        to_char(faces[1].colors[2][0].color), to_char(faces[1].colors[2][1].color), to_char(faces[1].colors[2][2].color)
    );

    printf("          %s  %s  %s\n", to_char(faces[2].colors[0][0].color), to_char(faces[2].colors[0][1].color), to_char(faces[2].colors[0][2].color));
    printf("          %s  %s  %s\n", to_char(faces[2].colors[1][0].color), to_char(faces[2].main_color), to_char(faces[2].colors[1][2].color));
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

int prompt_stop(Face faces[6], char* move_name) {
    int result;
    display_cube(faces);
    printf("Finished: \e[4;37m%s\e[0m.\nEnter 1 to continue on your own or 0 to let the computer go to the next step:\n\e[0;90m> ", move_name);
    scanf("%d", &result);
    printf("\e[0m");
    return result;
}

void solve_cube(Face faces[6]) {
    make_perfect_white_cross(faces);
    if (prompt_stop(faces, "white cross")) return;

    place_white_corners(faces);
    if (prompt_stop(faces, "white corners")) return;

    solve_crown(faces);
    reorient_cube(faces);
    if (prompt_stop(faces, "middle crown")) return;

    make_yellow_cross(faces);
    if (prompt_stop(faces, "yellow cross")) return;

    place_yellow_edges(faces);
    reorient_cube(faces);
    if (prompt_stop(faces, "yellow edges")) return;

    place_yellow_corners(faces);
    reorient_cube(faces);
    if (prompt_stop(faces, "yellow corners placement")) return;

    solve_yellow_corners(faces);
}
