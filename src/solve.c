#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "rubiks.h"
#include "solve.h"

bool has_white_cross(Face faces[6]) {
    return faces[3].colors[0][1].color == WHITE
        && faces[3].colors[1][0].color == WHITE
        && faces[3].colors[1][2].color == WHITE
        && faces[3].colors[2][1].color == WHITE
        && faces[3].main_color == WHITE;
}

bool has_yellow_cross(Face faces[6]) {
    return faces[2].colors[0][1].color == YELLOW
        && faces[2].colors[1][0].color == YELLOW
        && faces[2].colors[1][2].color == YELLOW
        && faces[2].colors[2][1].color == YELLOW
        && faces[2].main_color == YELLOW;
}

bool has_perfect_white_cross(Face faces[6]) {
    return has_white_cross(faces)
        && faces[0].colors[0][1].color == faces[0].main_color
        && faces[1].colors[0][1].color == faces[1].main_color
        && faces[4].colors[0][1].color == faces[4].main_color
        && faces[5].colors[0][1].color == faces[5].main_color;
    ;
}

bool has_perfect_yellow_cross(Face faces[6]) {
    return has_yellow_cross(faces)
        && faces[0].colors[2][1].color == faces[0].main_color
        && faces[1].colors[2][1].color == faces[1].main_color
        && faces[4].colors[2][1].color == faces[4].main_color
        && faces[5].colors[2][1].color == faces[5].main_color;
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

void make_perfect_white_cross(Face faces[6]) {
    if (faces[3].main_color != WHITE) {
        puts("White is not on top of the cube. TODO: Move it there.");
        return;
    }
    if (has_perfect_white_cross(faces))
        return;

    bool has_half_cross = faces[3].colors[0][1].color == WHITE
        && faces[3].colors[1][0].color == WHITE
        && faces[3].colors[1][2].color == WHITE
        && faces[4].colors[0][1].color == faces[4].colors[1][1].color
        && faces[5].colors[0][1].color == faces[5].colors[1][1].color
        && faces[1].colors[0][1].color == faces[1].colors[1][1].color;

    for (int i = 0; i < 4; i++) {
        // If we have 3 out of 4 white edges placed, and the fourth edge is inversed
        if (has_half_cross
            && faces[0].colors[0][1].color == WHITE
            && faces[3].colors[2][1].color == faces[0].main_color)
            run_move("F U' R U", faces);
        // If we have 3 out of 4 white edges placed, and the fourth one is on the front face at the bottom
        else if (has_half_cross && faces[0].colors[2][1].color == WHITE)
            run_move("F' R' D' R F F", faces);
        // If we have 3 out of 4 white edges placed, and the fourth one is on the from face on the right
        else if (has_half_cross
            && faces[0].colors[1][2].color == WHITE
            && faces[5].colors[1][0].color == faces[0].main_color)
            run_move("R' D' R F F", faces);
        // Mirror of the previous
        else if (has_half_cross
            && faces[0].colors[1][0].color == WHITE
            && faces[4].colors[1][2].color == faces[0].main_color)
            run_move("L D L' F F", faces);
        // If an edge piece is on the upper face on the bottom, inversed, and on the left of its main face
        else if (faces[3].colors[2][1].color == faces[5].main_color
            && faces[0].colors[0][1].color == faces[3].main_color)
            run_move("F R", faces);
        // If an edge piece is on the upper face on the right, inversed and at the opposite of its main face
        else if (faces[3].colors[1][2].color == faces[4].main_color
            && faces[5].colors[0][1].color == WHITE)
            run_move("R' F' U", faces);
        // Mirror of the previous
        else if (faces[3].colors[1][0].color == faces[5].main_color
            && faces[4].colors[0][1].color == WHITE)
            run_move("L F U'", faces);
        run_move("Y", faces);
    }
}

void place_white_corners(Face faces[6]) {
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

    if (   (faces[0].colors[2][2].color == faces[5].colors[1][1].color && faces[5].colors[2][0].color == WHITE && faces[2].colors[0][2].color==faces[0].colors[1][1].color)
        || (faces[0].colors[2][2].color == faces[5].colors[1][1].color && faces[5].colors[2][0].color == faces[0].colors[1][1].color && faces[2].colors[0][2].color==WHITE)

        || (faces[0].colors[2][2].color == WHITE && faces[5].colors[2][0].color == faces[5].colors[1][1].color && faces[2].colors[0][2].color == faces[0].colors[1][1].color)
        || (faces[0].colors[2][2].color == WHITE && faces[5].colors[2][0].color == faces[0].colors[1][1].color && faces[2].colors[0][2].color == faces[5].colors[1][1].color)

        || (faces[0].colors[2][2].color == faces[0].colors[1][1].color && faces[5].colors[2][0].color == faces[5].colors[1][1].color && faces[2].colors[0][2].color == WHITE)
        || (faces[0].colors[2][2].color == faces[0].colors[1][1].color && faces[5].colors[2][0].color == WHITE && faces[2].colors[0][2].color == faces[5].colors[1][1].color)  // green and red faces
        //All the possible combinations on face DOWN

        || (faces[0].colors[0][2].color == faces[5].colors[1][1].color && faces[5].colors[0][0].color == WHITE && faces[3].colors[2][2].color==faces[0].colors[1][1].color)
        || (faces[0].colors[0][2].color == faces[5].colors[1][1].color && faces[5].colors[0][0].color == faces[0].colors[1][1].color && faces[3].colors[2][2].color==WHITE)

        || (faces[0].colors[0][2].color == WHITE && faces[5].colors[0][0].color == faces[5].colors[1][1].color && faces[3].colors[2][2].color == faces[0].colors[1][1].color)
        || (faces[0].colors[0][2].color == WHITE && faces[5].colors[0][0].color == faces[0].colors[1][1].color && faces[3].colors[2][2].color == faces[5].colors[1][1].color)

        || (faces[0].colors[0][2].color == faces[0].colors[1][1].color && faces[5].colors[0][0].color == WHITE && faces[3].colors[2][2].color == faces[5].colors[1][1].color)  ){// green and red faces
        //All the possible combinations on face UP

        run_move("R' D' R D", faces);


    }
    if (   (faces[5].colors[2][2].color == faces[1].colors[1][1].color && faces[1].colors[2][0].color == WHITE && faces[2].colors[2][2].color==faces[5].colors[1][1].color)
        || (faces[5].colors[2][2].color == faces[1].colors[1][1].color && faces[1].colors[2][0].color == faces[5].colors[1][1].color && faces[2].colors[2][2].color==WHITE)

        || (faces[5].colors[2][2].color == WHITE && faces[1].colors[2][0].color == faces[5].colors[1][1].color && faces[2].colors[2][2].color == faces[1].colors[1][1].color)
        || (faces[5].colors[2][2].color == WHITE && faces[1].colors[2][0].color == faces[1].colors[1][1].color && faces[2].colors[2][2].color == faces[5].colors[1][1].color)

        || (faces[5].colors[2][2].color == faces[5].colors[1][1].color && faces[1].colors[2][0].color == WHITE && faces[2].colors[2][2].color == faces[1].colors[1][1].color)
        || (faces[5].colors[2][2].color == faces[5].colors[1][1].color && faces[1].colors[2][0].color == faces[1].colors[1][1].color && faces[2].colors[2][2].color == WHITE)  // red and blue faces
        //All the possible combinations on face DOWN

        || (faces[5].colors[0][2].color == faces[1].colors[1][1].color && faces[1].colors[0][0].color == WHITE && faces[3].colors[0][2].color==faces[5].colors[1][1].color)
        || (faces[5].colors[0][2].color == faces[1].colors[1][1].color && faces[1].colors[0][0].color == faces[5].colors[1][1].color && faces[3].colors[0][2].color==WHITE)

        || (faces[5].colors[0][2].color == WHITE && faces[1].colors[0][0].color == faces[5].colors[1][1].color && faces[3].colors[0][2].color == faces[1].colors[1][1].color)
        || (faces[5].colors[0][2].color == WHITE && faces[1].colors[0][0].color == faces[1].colors[1][1].color && faces[3].colors[0][2].color == faces[5].colors[1][1].color)

        || (faces[5].colors[0][2].color == faces[5].colors[1][1].color && faces[1].colors[0][0].color == WHITE && faces[3].colors[2][2].color == faces[1].colors[1][1].color)  ){
        //All the possible combinations on face UP

        run_move("B' D' B D", faces);
    }


    if (   (faces[1].colors[2][2].color == faces[4].colors[1][1].color && faces[4].colors[2][0].color == WHITE && faces[2].colors[2][0].color==faces[1].colors[1][1].color)
        || (faces[1].colors[2][2].color == faces[4].colors[1][1].color && faces[4].colors[2][0].color == faces[1].colors[1][1].color && faces[2].colors[0][2].color==WHITE)

        || (faces[1].colors[2][2].color == WHITE && faces[4].colors[2][0].color == faces[1].colors[1][1].color && faces[2].colors[2][0].color == faces[4].colors[1][1].color)
        || (faces[1].colors[2][2].color == WHITE && faces[4].colors[2][0].color == faces[4].colors[1][1].color && faces[2].colors[2][0].color == faces[1].colors[1][1].color)

        || (faces[1].colors[2][2].color == faces[1].colors[1][1].color && faces[4].colors[2][0].color == WHITE && faces[2].colors[2][0].color == faces[4].colors[1][1].color)
        || (faces[1].colors[2][2].color == faces[1].colors[1][1].color && faces[4].colors[2][0].color == faces[4].colors[1][1].color && faces[2].colors[2][0].color == WHITE)  // blue and orange faces
        //All the possible combinations on face DOWN

        || (faces[1].colors[2][2].color == faces[4].colors[1][1].color && faces[4].colors[2][0].color == WHITE && faces[3].colors[0][0].color==faces[1].colors[1][1].color)
        || (faces[1].colors[2][2].color == faces[4].colors[1][1].color && faces[4].colors[2][0].color == faces[1].colors[1][1].color && faces[3].colors[0][0].color==WHITE)

        || (faces[1].colors[2][2].color == WHITE && faces[4].colors[2][0].color == faces[1].colors[1][1].color && faces[3].colors[0][0].color == faces[4].colors[1][1].color)
        || (faces[1].colors[2][2].color == WHITE && faces[4].colors[2][0].color == faces[4].colors[1][1].color && faces[3].colors[0][0].color == faces[1].colors[1][1].color)

        || (faces[1].colors[2][2].color == faces[1].colors[1][1].color && faces[4].colors[2][0].color == WHITE && faces[3].colors[2][0].color == faces[4].colors[1][1].color)  ) {
        //All the possible combinations on face UP

        run_move("L' D' L D", faces);
    }


    if (   (faces[4].colors[2][2].color == faces[0].colors[1][1].color && faces[0].colors[2][0].color == WHITE && faces[2].colors[0][0].color==faces[4].colors[1][1].color)
        || (faces[4].colors[2][2].color == faces[0].colors[1][1].color && faces[0].colors[2][0].color == faces[4].colors[1][1].color && faces[2].colors[0][0].color==WHITE)

        || (faces[4].colors[2][2].color == WHITE && faces[0].colors[2][0].color == faces[4].colors[1][1].color && faces[2].colors[0][0].color == faces[0].colors[1][1].color)
        || (faces[4].colors[2][2].color == WHITE && faces[0].colors[2][0].color == faces[0].colors[1][1].color && faces[2].colors[0][0].color == faces[4].colors[1][1].color)

        || (faces[4].colors[2][2].color == faces[4].colors[1][1].color && faces[0].colors[2][0].color == WHITE && faces[2].colors[0][0].color == faces[0].colors[1][1].color)
        || (faces[4].colors[2][2].color == faces[4].colors[1][1].color && faces[0].colors[2][0].color == faces[0].colors[1][1].color && faces[2].colors[0][0].color == WHITE)  //orange and green faces
        //All the possible combinations on face DOWN

        || (faces[4].colors[2][2].color == faces[0].colors[1][1].color && faces[0].colors[2][0].color == WHITE && faces[3].colors[0][2].color==faces[4].colors[1][1].color)
        || (faces[4].colors[2][2].color == faces[0].colors[1][1].color && faces[0].colors[2][0].color == faces[4].colors[1][1].color && faces[3].colors[0][2].color==WHITE)

        || (faces[4].colors[2][2].color == WHITE && faces[0].colors[2][0].color == faces[4].colors[1][1].color && faces[3].colors[0][2].color == faces[0].colors[1][1].color)
        || (faces[4].colors[2][2].color == WHITE && faces[0].colors[2][0].color == faces[0].colors[1][1].color && faces[3].colors[0][2].color == faces[4].colors[1][1].color)

        || (faces[4].colors[2][2].color == faces[4].colors[1][1].color && faces[0].colors[2][0].color == WHITE && faces[3].colors[0][0].color == faces[0].colors[1][1].color)   ){
        //All the possible combinations on face UP


        run_move("F' D' F D", faces);
    }


    if((faces[3].colors[0][0].color!=WHITE || faces[3].colors[0][1].color!=WHITE || faces[3].colors[0][2].color!=WHITE
    || faces[3].colors[1][0].color!=WHITE || faces[3].colors[1][1].color!=WHITE || faces[3].colors[1][2].color!=WHITE
    || faces[3].colors[2][0].color!=WHITE || faces[3].colors[2][1].color!=WHITE || faces[3].colors[2][2].color!=WHITE)){
        run_move("D", faces);

        place_white_corners(faces);
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
    if (faces[2].main_color != YELLOW) {
        puts("Yellow is not on the bottom of the cube. TODO: Move it there.");
        return;
    }
    if (has_yellow_cross(faces))
        return;

    // Yellow L
    bool done_l = false;
    for (int i = 0; i < 4; i++) {
        if (!done_l && faces[2].colors[0][1].color == YELLOW && faces[2].colors[1][0].color == YELLOW) {
            run_move("ZZYY R' U' F' U F R YYZZ", faces);
            done_l = true;
        }
        run_move("Y", faces);
    }
    if (done_l)
        return;

    // Yellow horrizontal line
    if (faces[2].colors[1][0].color == YELLOW && faces[2].colors[1][2].color == YELLOW)
        run_move("ZZ F R U R' U' F' ZZ", faces);
    // Yellow vertical line
    else if (faces[2].colors[0][1].color == YELLOW && faces[2].colors[2][1].color == YELLOW)
        run_move("ZZ Y F R U R' U' F' ZZ", faces);
    // If we have neither
    else
        run_move("ZZ R' U' F' U F R F R U R' U' F' ZZ", faces);
}

void place_yellow_edges(Face faces[6]) {
    if (has_perfect_yellow_cross(faces))
        return;

    // Two opposite edges
    for (int i = 0; i < 4; i++) {
        if (faces[0].colors[2][1].color == faces[0].main_color && faces[1].colors[2][1].color == faces[1].main_color) {
            run_move("ZZ R U U R' U' R U' R' ZZ", faces);
            break;
        }
        run_move("D", faces);
    }

    // Two adjacent edges
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (faces[1].colors[2][1].color == faces[1].main_color && faces[4].colors[2][1].color == faces[4].main_color) {
                run_move("ZZY' R U U R' U' R U' R' U' YZZ", faces);
                return;
            }
            run_move("D", faces);
        }
        run_move("Y", faces);
    }
}

bool includes(Color arr[3], Color value) {
    for (int i = 0; i < 3; i++) {
        if (arr[i] == value)
            return true;
    }
    return false;
}

void place_yellow_corners(Face faces[6]) {
    Color top_lft_colors[3] = { faces[2].colors[0][0].color, faces[0].colors[2][0].color, faces[4].colors[2][2].color };
    Color top_rgt_colors[3] = { faces[2].colors[0][2].color, faces[0].colors[2][2].color, faces[5].colors[2][0].color };
    Color bot_lft_colors[3] = { faces[2].colors[2][0].color, faces[4].colors[2][0].color, faces[1].colors[2][2].color };
    Color bot_rgt_colors[3] = { faces[2].colors[2][2].color, faces[5].colors[2][2].color, faces[1].colors[2][0].color };

    bool is_top_lft_placed = includes(top_lft_colors, faces[2].main_color) && includes(top_lft_colors, faces[0].main_color) && includes(top_lft_colors, faces[4].main_color);
    bool is_top_rgt_placed = includes(top_rgt_colors, faces[2].main_color) && includes(top_rgt_colors, faces[0].main_color) && includes(top_rgt_colors, faces[5].main_color);
    bool is_bot_lft_placed = includes(bot_lft_colors, faces[2].main_color) && includes(bot_lft_colors, faces[1].main_color) && includes(bot_lft_colors, faces[4].main_color);
    bool is_bot_rgt_placed = includes(bot_rgt_colors, faces[2].main_color) && includes(bot_rgt_colors, faces[1].main_color) && includes(bot_rgt_colors, faces[5].main_color);

    // If every corner is well placed
    if (is_bot_lft_placed && is_bot_rgt_placed && is_bot_lft_placed && is_bot_rgt_placed)
        return;
    // If every corner is misplaced
    if (!is_bot_lft_placed && !is_bot_rgt_placed && !is_bot_lft_placed && !is_bot_rgt_placed) {
        run_move("ZZY' L' U R U' L U R' U' YZZ", faces);
        place_yellow_corners(faces);
        return;
    }

    if (is_top_lft_placed)
        run_move("Y Y", faces);
    if (is_top_rgt_placed)
        run_move("Y'", faces);
    if (is_bot_lft_placed)
        run_move("Y", faces);

    run_move("ZZYY L' U R U' L U R' U' YYZZ", faces);
    place_yellow_corners(faces);
}

void solve_yellow_corners() {}
