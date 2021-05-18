#include <stdbool.h>
#include "rubiks.h"

bool expect_result(Face faces[6], Face expected[6]) {
    for (int face = 0; face < 6; face++) {
        if (faces[face].main_color != expected[face].main_color)
            return false;

        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (faces[face].colors[row][col].color != expected[face].colors[row][col].color)
                    return false;
                }
        }
    }
    return true;
}

bool test_many(Face faces[6]) {
    Face first_expected[6] = {
        // Front
        { .colors = {
            { { .color = GREEN }, { .color = GREEN }, { .color = GREEN } },
            { { .color = WHITE }, { .color = GREEN }, { .color = YELLOW } },
            { { .color = RED }, { .color = BLUE }, { .color = YELLOW } },
        }, .main_color = GREEN },
        // Back
        { .colors = {
            { { .color = ORANGE }, { .color = BLUE }, { .color = YELLOW } },
            { { .color = GREEN }, { .color = BLUE }, { .color = YELLOW } },
            { { .color = BLUE }, { .color = YELLOW }, { .color = YELLOW } },
        }, .main_color = BLUE },
        // Down
        { .colors = {
            { { .color = BLUE }, { .color = WHITE }, { .color = ORANGE } },
            { { .color = ORANGE }, { .color = YELLOW }, { .color = GREEN } },
            { { .color = RED }, { .color = RED }, { .color = RED } },
        }, .main_color = YELLOW },
        // Up
        { .colors = {
            { { .color = ORANGE }, { .color = RED }, { .color = WHITE } },
            { { .color = GREEN }, { .color = WHITE }, { .color = WHITE } },
            { { .color = RED }, { .color = WHITE }, { .color = ORANGE } },
        }, .main_color = WHITE },
        // Left
        { .colors = {
            { { .color = GREEN }, { .color = RED }, { .color = WHITE } },
            { { .color = ORANGE }, { .color = ORANGE }, { .color = ORANGE } },
            { { .color = GREEN }, { .color = BLUE }, { .color = YELLOW } },
        }, .main_color = ORANGE },
        // Right
        { .colors = {
            { { .color = WHITE }, { .color = RED }, { .color = BLUE } },
            { { .color = BLUE }, { .color = RED }, { .color = YELLOW } },
            { { .color = BLUE }, { .color = ORANGE }, { .color = WHITE } },
        }, .main_color = RED },
    };

    Face second_expected[6] = {
        // Front
        { .colors = {
            { { .color = RED }, { .color = RED }, { .color = RED } },
            { { .color = BLUE }, { .color = GREEN }, { .color = ORANGE } },
            { { .color = BLUE }, { .color = GREEN }, { .color = ORANGE } },
        }, .main_color = GREEN },
        // Back
        { .colors = {
            { { .color = BLUE }, { .color = BLUE }, { .color = ORANGE } },
            { { .color = ORANGE }, { .color = BLUE }, { .color = GREEN } },
            { { .color = BLUE }, { .color = BLUE }, { .color = GREEN } },
        }, .main_color = BLUE },
        // Down
        { .colors = {
            { { .color = YELLOW }, { .color = YELLOW }, { .color = BLUE } },
            { { .color = YELLOW }, { .color = YELLOW }, { .color = BLUE } },
            { { .color = WHITE }, { .color = WHITE }, { .color = WHITE } },
        }, .main_color = YELLOW },
        // Up
        { .colors = {
            { { .color = GREEN }, { .color = ORANGE }, { .color = WHITE } },
            { { .color = RED }, { .color = WHITE }, { .color = GREEN } },
            { { .color = GREEN }, { .color = GREEN }, { .color = GREEN } },
        }, .main_color = WHITE },
        // Left
        { .colors = {
            { { .color = YELLOW }, { .color = WHITE }, { .color = YELLOW } },
            { { .color = ORANGE }, { .color = ORANGE }, { .color = RED } },
            { { .color = ORANGE }, { .color = RED }, { .color = RED } },
        }, .main_color = ORANGE },
        // Right
        { .colors = {
            { { .color = WHITE }, { .color = WHITE }, { .color = RED } },
            { { .color = YELLOW }, { .color = RED }, { .color = WHITE } },
            { { .color = YELLOW }, { .color = YELLOW }, { .color = ORANGE } },
        }, .main_color = RED },
    };

    Face third_expected[6] = {
        // Front
        { .colors = {
            { { .color = ORANGE }, { .color = RED }, { .color = WHITE } },
            { { .color = YELLOW }, { .color = GREEN }, { .color = YELLOW } },
            { { .color = BLUE }, { .color = BLUE }, { .color = RED } },
        }, .main_color = GREEN },
        // Back
        { .colors = {
            { { .color = GREEN }, { .color = RED }, { .color = GREEN } },
            { { .color = GREEN }, { .color = BLUE }, { .color = YELLOW } },
            { { .color = GREEN }, { .color = GREEN }, { .color = ORANGE } },
        }, .main_color = BLUE },
        // Down
        { .colors = {
            { { .color = YELLOW }, { .color = RED }, { .color = BLUE } },
            { { .color = WHITE }, { .color = YELLOW }, { .color = GREEN } },
            { { .color = BLUE }, { .color = ORANGE }, { .color = RED } },
        }, .main_color = YELLOW },
        // Up
        { .colors = {
            { { .color = WHITE }, { .color = GREEN }, { .color = ORANGE } },
            { { .color = BLUE }, { .color = WHITE }, { .color = WHITE } },
            { { .color = WHITE }, { .color = WHITE }, { .color = GREEN } },
        }, .main_color = WHITE },
        // Left
        { .colors = {
            { { .color = RED }, { .color = ORANGE }, { .color = BLUE } },
            { { .color = RED }, { .color = ORANGE }, { .color = ORANGE } },
            { { .color = YELLOW }, { .color = BLUE }, { .color = RED } },
        }, .main_color = ORANGE },
        // Right
        { .colors = {
            { { .color = ORANGE }, { .color = ORANGE }, { .color = YELLOW } },
            { { .color = BLUE }, { .color = RED }, { .color = YELLOW } },
            { { .color = WHITE }, { .color = WHITE }, { .color = YELLOW } },
        }, .main_color = RED },
    };

    bool result;
    run_move("L' R' R' D R' L' F' B B D F L' L R U' F R' L L' U D R L U B' B' B", faces);
    result = expect_result(faces, first_expected);
    if (!result)
        return false;

    create_cube(faces);
    run_move("U D' B D U' L' F R' D B D B F' R' U' U L' U", faces);
    result = expect_result(faces, second_expected);
    if (!result)
        return false;

    create_cube(faces);
    run_move("B D' R' D B U D' U D' B F' L' F' L L B L D U L' D U U R' R' U F L' B'", faces);
    result = expect_result(faces, third_expected);

    create_cube(faces);
    return result;
}
