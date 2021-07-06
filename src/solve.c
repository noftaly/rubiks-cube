#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "rubiks.h"
#include "solve.h"

bool has_white_cross(Face faces[6]) {
    return faces[3].colors[0][1] == WHITE
        && faces[3].colors[1][0] == WHITE
        && faces[3].colors[1][2] == WHITE
        && faces[3].colors[2][1] == WHITE
        && faces[3].colors[1][1] == WHITE;
}

bool has_white_face(Face faces[6]) {
    return faces[3].colors[0][0] == WHITE && faces[3].colors[0][1] == WHITE && faces[3].colors[0][2] == WHITE
        && faces[3].colors[1][0] == WHITE && faces[3].colors[1][1] == WHITE && faces[3].colors[1][2] == WHITE
        && faces[3].colors[2][0] == WHITE && faces[3].colors[2][1] == WHITE && faces[3].colors[2][2] == WHITE;
}

bool has_crown(Face faces[6]) {
    for (int i = 0; i < 6; i++) {
        if (i == 2 || i == 3) continue;

        if (faces[i].colors[1][0] != faces[i].colors[1][1] || faces[i].colors[1][1] != faces[i].colors[1][2])
            return false;
    }
    return true;
}

bool has_yellow_cross(Face faces[6]) {
    return faces[2].colors[0][1] == YELLOW
        && faces[2].colors[1][0] == YELLOW
        && faces[2].colors[1][2] == YELLOW
        && faces[2].colors[2][1] == YELLOW
        && faces[2].colors[1][1] == YELLOW;
}

bool has_perfect_white_cross(Face faces[6]) {
    return has_white_cross(faces)
        && faces[0].colors[0][1] == faces[0].colors[1][1]
        && faces[1].colors[0][1] == faces[1].colors[1][1]
        && faces[4].colors[0][1] == faces[4].colors[1][1]
        && faces[5].colors[0][1] == faces[5].colors[1][1];
    ;
}

bool has_perfect_yellow_cross(Face faces[6]) {
    return has_yellow_cross(faces)
        && faces[0].colors[2][1] == faces[0].colors[1][1]
        && faces[1].colors[2][1] == faces[1].colors[1][1]
        && faces[4].colors[2][1] == faces[4].colors[1][1]
        && faces[5].colors[2][1] == faces[5].colors[1][1];
}

bool has_white_edge_on_down(Face faces[6]) {
    return faces[2].colors[0][1] == WHITE || faces[2].colors[1][0] == WHITE || faces[2].colors[1][2] == WHITE || faces[2].colors[2][1] == WHITE
        || faces[0].colors[2][1] == WHITE || faces[5].colors[2][1] == WHITE || faces[1].colors[2][1] == WHITE || faces[4].colors[2][1] == WHITE;
}

bool includes(Color arr[3], Color value) {
    for (int i = 0; i < 3; i++) {
        if (arr[i] == value)
            return true;
    }
    return false;
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

int get_previous_face(int index) {
    switch(index) {
        case 0: return 4;
        case 1: return 5;
        case 4: return 1;
        case 5: return 0;
        default: return -1;
    }
}


void rise_white_edge(Face faces[6], int iteration) {
    if (iteration > 20) {
        return;
    }
    // If a cube is below
    if (faces[2].colors[0][1] == WHITE)
        run_move("FF", faces);
    // If a cube is on the left
    else if (faces[4].colors[1][2] == WHITE)
        run_move("F", faces);
    // If a cube is on the right
    else if (faces[5].colors[1][0] == WHITE)
        run_move("F'", faces);
    // If a cube is on the front face, at the bottom
    else if (faces[0].colors[2][1] == WHITE)
        run_move("F' U' R U", faces);
    // If a cube is on the front face, at the right
    else if (faces[0].colors[1][2] == WHITE)
        run_move("U' R U", faces);
    // If a cube is on the front face, at the left
    else if (faces[0].colors[1][0] == WHITE)
        run_move("F F U' R U", faces);
    // If a cube is on the front face, at the top
    else if (faces[0].colors[0][1] == WHITE)
        run_move("F U' R U", faces);
    else {
        if (!has_white_edge_on_down(faces)) {
            if (faces[5].colors[1][2] == WHITE || faces[1].colors[1][0] == WHITE)
                run_move("B' D' B", faces);
            else if (faces[4].colors[1][0] == WHITE || faces[1].colors[1][2] == WHITE)
                run_move("B D B'", faces);
        }
        run_move("D", faces);
        rise_white_edge(faces, iteration + 1);
    }
}

void make_white_cross(Face faces[6]) {
    if (faces[3].colors[1][1] != WHITE) {
        puts("White is not on top of the cube. TODO: Move it there.");
        return;
    }
    if (has_white_cross(faces))
        return;

    for (int i = 0; i < 4; i++) {
        if (faces[3].colors[2][1] != WHITE)
            rise_white_edge(faces, 0);
        run_move("Y", faces);
    }
}

void place_white_edges(Face faces[6]) {
    if (faces[3].colors[1][1] != WHITE) {
        puts("White is not on top of the cube. TODO: Move it there.");
        return;
    }
    if (has_perfect_white_cross(faces))
        return;

    while (faces[0].colors[0][1] != faces[0].colors[1][1])
        run_move("U", faces);

    while (!has_perfect_white_cross(faces)) {
        run_move("Y", faces);
        if (faces[0].colors[0][1] == faces[0].colors[1][1])
            continue;
        if (faces[5].colors[0][1] == faces[0].colors[1][1])
            run_move("F F D R R D' F F", faces);
        else if (faces[1].colors[0][1] == faces[0].colors[1][1])
            run_move("F F D D B B D D F F", faces);
    }
}

void place_white_corners(Face faces[6]) {
    while (!has_white_face(faces)) {
        for (int i = 0; i < 8; i++){
            Color front_top_right = faces[0].colors[0][2];
            Color front_middle = faces[0].colors[1][1];
            Color front_bottom_right = faces[0].colors[2][2];
            Color right_top_left = faces[5].colors[0][0];
            Color right_middle = faces[5].colors[1][1];
            Color right_bottom_left = faces[5].colors[2][0];
            Color up_bottom_right = faces[3].colors[2][2];
            Color down_top_right = faces[2].colors[0][2];
            // 0=front, 1=back, 2=down, 3=up, 4=left, 5=right

            bool is_down_valid = false;
            bool is_up_valid = false;
            int faces_matrix[6][3] = { { 5, 3, 0 }, { 5, 0, 3 }, { 3, 5, 0 }, { 3, 0, 5 }, { 0, 3, 5 }, { 0, 5, 3 } };
            for (int j = 0; j < 6; j++)
                is_down_valid = is_down_valid || (front_bottom_right == faces[faces_matrix[j][0]].colors[1][1] && right_bottom_left == faces[faces_matrix[j][1]].colors[1][1] && down_top_right == faces[faces_matrix[j][2]].colors[1][1]);

            for (int j = 0; j < 5; j++)
                is_up_valid = is_up_valid || (front_top_right == faces[faces_matrix[j][0]].colors[1][1] && right_top_left == faces[faces_matrix[j][1]].colors[1][1] && up_bottom_right == faces[faces_matrix[j][2]].colors[1][1]);

            if (is_down_valid || is_up_valid) {
                run_move("R' D' R D", faces);
            } else if (
                   (right_top_left == WHITE && front_top_right != right_middle && up_bottom_right != front_middle)
                || (right_top_left == WHITE && front_top_right != front_middle && up_bottom_right != right_middle)

                || (front_top_right == WHITE && right_top_left != right_middle && up_bottom_right != front_middle)
                || (front_top_right == WHITE && right_top_left != front_middle && up_bottom_right != right_middle)

                || (up_bottom_right == WHITE && front_top_right != front_middle && up_bottom_right != right_middle)
                || (up_bottom_right == WHITE && front_top_right != front_middle && right_top_left != right_middle)) {
                run_move("R' D' R", faces);
            } else {
                run_move("D", faces);
            }
        }
        run_move("Y", faces);
    }
    run_move("Y'", faces);
}

void solve_crown(Face faces[6]) {
    run_move("ZZ", faces);
    int iteration = 0;
    while (iteration < 100 && !has_crown(faces)) {
        for (int i = 0; i < 4; i++) {
            if (faces[0].colors[1][2] == faces[5].colors[1][1] && faces[5].colors[1][0] == faces[0].colors[1][1])
                run_move("U R U' R' U' F' U F U' R U' R' U' F' U F", faces);
            if (faces[0].colors[0][1] != faces[0].colors[1][1]) {
                run_move("U", faces);
                continue;
            }

            Color upper_edge = faces[3].colors[2][1];
            if (upper_edge == faces[4].colors[1][1]) {
                run_move("U' L' U L U F U' F'", faces);
            } else if (upper_edge == faces[5].colors[1][1]) {
                run_move("U R U' R' U' F' U F", faces);
            } else {
                // In case we noticed something unrelated but that can block the flow later on, we unblock it.
                if (faces[0].colors[1][0] != YELLOW && faces[4].colors[1][2] != YELLOW)
                    run_move("L' U L U F U' F'", faces);
                run_move("U", faces);
                continue;
            }
            // Pretty sure this can never happen, the one at the top of the loop should solve it.
            if (faces[0].colors[1][2] == faces[5].colors[1][1] && faces[5].colors[1][0] == faces[0].colors[1][1])
                run_move("U R U' R' U' F' U F U' R U' R' U' F' U F", faces);
            break;
        }
        run_move("Y", faces);
        iteration++;
    }
    run_move("ZZ", faces);
}

void make_yellow_cross(Face faces[6]) {
    if (faces[2].colors[1][1] != YELLOW) {
        puts("Yellow is not on the bottom of the cube. TODO: Move it there.");
        return;
    }
    if (has_yellow_cross(faces))
        return;

    // Yellow L
    bool done_l = false;
    for (int i = 0; i < 4; i++) {
        if (!done_l && faces[2].colors[0][1] == YELLOW && faces[2].colors[1][0] == YELLOW) {
            run_move("ZZYY R' U' F' U F R YYZZ", faces);
            done_l = true;
        }
        run_move("Y", faces);
    }
    if (done_l)
        return;

    // Yellow horrizontal line
    if (faces[2].colors[1][0] == YELLOW && faces[2].colors[1][2] == YELLOW)
        run_move("ZZ F R U R' U' F' ZZ", faces);
    // Yellow vertical line
    else if (faces[2].colors[0][1] == YELLOW && faces[2].colors[2][1] == YELLOW)
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
        if (faces[0].colors[2][1] == faces[0].colors[1][1] && faces[1].colors[2][1] == faces[1].colors[1][1]) {
            run_move("ZZ R U U R' U' R U' R' ZZ", faces);
            break;
        }
        run_move("D", faces);
    }

    // Two adjacent edges
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (faces[1].colors[2][1] == faces[1].colors[1][1] && faces[4].colors[2][1] == faces[4].colors[1][1]) {
                run_move("ZZY' R U U R' U' R U' R' U' YZZ", faces);
                return;
            }
            run_move("D", faces);
        }
        run_move("Y", faces);
    }
}

void place_yellow_corners(Face faces[6]) {
    Color top_lft_colors[3] = { faces[2].colors[0][0], faces[0].colors[2][0], faces[4].colors[2][2] };
    Color top_rgt_colors[3] = { faces[2].colors[0][2], faces[0].colors[2][2], faces[5].colors[2][0] };
    Color bot_lft_colors[3] = { faces[2].colors[2][0], faces[4].colors[2][0], faces[1].colors[2][2] };
    Color bot_rgt_colors[3] = { faces[2].colors[2][2], faces[5].colors[2][2], faces[1].colors[2][0] };

    bool is_top_lft_placed = includes(top_lft_colors, faces[2].colors[1][1]) && includes(top_lft_colors, faces[0].colors[1][1]) && includes(top_lft_colors, faces[4].colors[1][1]);
    bool is_top_rgt_placed = includes(top_rgt_colors, faces[2].colors[1][1]) && includes(top_rgt_colors, faces[0].colors[1][1]) && includes(top_rgt_colors, faces[5].colors[1][1]);
    bool is_bot_lft_placed = includes(bot_lft_colors, faces[2].colors[1][1]) && includes(bot_lft_colors, faces[1].colors[1][1]) && includes(bot_lft_colors, faces[4].colors[1][1]);
    bool is_bot_rgt_placed = includes(bot_rgt_colors, faces[2].colors[1][1]) && includes(bot_rgt_colors, faces[1].colors[1][1]) && includes(bot_rgt_colors, faces[5].colors[1][1]);

    // If every corner is well placed
    if (is_bot_lft_placed && is_bot_rgt_placed && is_bot_lft_placed && is_bot_rgt_placed)
        return;
    // If every corner is misplaced
    if (!is_bot_lft_placed && !is_bot_rgt_placed && !is_bot_lft_placed && !is_bot_rgt_placed) {
        run_move("ZZY' L' U R U' L U R' U' YZZ", faces);
        place_yellow_corners(faces);
        return;
    }

    // Place the only well-placed corner on the bottom right
    if (is_top_lft_placed)
        run_move("Y Y", faces);
    if (is_top_rgt_placed)
        run_move("Y'", faces);
    if (is_bot_lft_placed)
        run_move("Y", faces);

    run_move("ZZYY L' U R U' L U R' U' YYZZ", faces);
    // Re-call the function
    place_yellow_corners(faces);
}

void solve_yellow_corners(Face faces[6]) {
    run_move("ZZ", faces);
    for (int i = 0; i < 4; i++) {
        if (faces[5].colors[0][0] == YELLOW)
            run_move("R' D' R D   R' D' R D", faces);
        if (faces[0].colors[0][2] == YELLOW)
            run_move("R' D' R D   R' D' R D   R' D' R D   R' D' R D", faces);
        run_move("U'", faces);
    }
    run_move("ZZ", faces);
}
