#include <stdio.h>
#include <stdbool.h>
#include "rubiks.h"
#include "solve.h"

// Basic movements
Face move_expected_1[6] = {
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

Face move_expected_2[6] = {
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

Face move_expected_3[6] = {
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

// White cross
Face perfect_white_cross_expected[6] = {
    // Front
    { .colors = {
        { { .color = UNSET }, { .color = GREEN }, { .color = UNSET } },
        { { .color = UNSET }, { .color = GREEN }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = GREEN },
    // Back
    { .colors = {
        { { .color = UNSET }, { .color = BLUE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = BLUE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = BLUE },
    // Down
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = YELLOW }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = YELLOW },
    // Up
    { .colors = {
        { { .color = UNSET }, { .color = WHITE }, { .color = UNSET } },
        { { .color = WHITE }, { .color = WHITE }, { .color = WHITE } },
        { { .color = UNSET }, { .color = WHITE }, { .color = UNSET } },
    }, .main_color = WHITE },
    // Left
    { .colors = {
        { { .color = UNSET }, { .color = ORANGE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = ORANGE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = ORANGE },
    // Right
    { .colors = {
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = RED },
};

Face white_cross_base_1[6] = {
    // Front
    { .colors = {
        { { .color = UNSET }, { .color = WHITE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = GREEN }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = GREEN },
    // Back
    { .colors = {
        { { .color = UNSET }, { .color = BLUE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = BLUE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = BLUE },
    // Down
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = YELLOW }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = YELLOW },
    // Up
    { .colors = {
        { { .color = UNSET }, { .color = WHITE }, { .color = UNSET } },
        { { .color = WHITE }, { .color = WHITE }, { .color = WHITE } },
        { { .color = UNSET }, { .color = GREEN }, { .color = UNSET } },
    }, .main_color = WHITE },
    // Left
    { .colors = {
        { { .color = UNSET }, { .color = ORANGE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = ORANGE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = ORANGE },
    // Right
    { .colors = {
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = RED },
};

Face white_cross_base_2[6] = {
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = GREEN }, { .color = UNSET } },
        { { .color = UNSET }, { .color = WHITE }, { .color = UNSET } },
    }, .main_color = GREEN },
    // Back
    { .colors = {
        { { .color = UNSET }, { .color = BLUE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = BLUE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = BLUE },
    // Down
    { .colors = {
        { { .color = UNSET }, { .color = GREEN }, { .color = UNSET } },
        { { .color = UNSET }, { .color = YELLOW }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = YELLOW },
    // Up
    { .colors = {
        { { .color = UNSET }, { .color = WHITE }, { .color = UNSET } },
        { { .color = WHITE }, { .color = WHITE }, { .color = WHITE } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = WHITE },
    // Left
    { .colors = {
        { { .color = UNSET }, { .color = ORANGE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = ORANGE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = ORANGE },
    // Right
    { .colors = {
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = RED },
};

Face white_cross_base_3[6] = {
    // Front
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = GREEN }, { .color = WHITE } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = GREEN },
    // Back
    { .colors = {
        { { .color = UNSET }, { .color = BLUE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = BLUE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = BLUE },
    // Down
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = YELLOW }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = YELLOW },
    // Up
    { .colors = {
        { { .color = UNSET }, { .color = WHITE }, { .color = UNSET } },
        { { .color = WHITE }, { .color = WHITE }, { .color = WHITE } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = WHITE },
    // Left
    { .colors = {
        { { .color = UNSET }, { .color = ORANGE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = ORANGE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = ORANGE },
    // Right
    { .colors = {
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
        { { .color = GREEN }, { .color = RED }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = RED },
};

Face white_cross_base_3_bis[6] = {
    // Front
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = WHITE }, { .color = GREEN }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = GREEN },
    // Back
    { .colors = {
        { { .color = UNSET }, { .color = BLUE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = BLUE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = BLUE },
    // Down
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = YELLOW }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = YELLOW },
    // Up
    { .colors = {
        { { .color = UNSET }, { .color = WHITE }, { .color = UNSET } },
        { { .color = WHITE }, { .color = WHITE }, { .color = WHITE } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = WHITE },
    // Left
    { .colors = {
        { { .color = UNSET }, { .color = ORANGE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = ORANGE }, { .color = GREEN } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = ORANGE },
    // Right
    { .colors = {
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = RED },
};

Face white_cross_base_4[6] = {
    // Front
    { .colors = {
        { { .color = UNSET }, { .color = WHITE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = GREEN }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = GREEN },
    // Back
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = BLUE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = BLUE },
    // Down
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = YELLOW }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = YELLOW },
    // Up
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = WHITE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
    }, .main_color = WHITE },
    // Left
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = ORANGE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = ORANGE },
    // Right
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = RED },
};
Face white_cross_expected_4[6] = {
    // Front
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = GREEN }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = GREEN },
    // Back
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = BLUE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = BLUE },
    // Down
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = YELLOW }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = YELLOW },
    // Up
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = WHITE }, { .color = WHITE } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = WHITE },
    // Left
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = ORANGE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = ORANGE },
    // Right
    { .colors = {
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = RED },
};

Face white_cross_base_5[6] = {
    // Front
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = GREEN }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = GREEN },
    // Back
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = BLUE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = BLUE },
    // Down
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = YELLOW }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = YELLOW },
    // Up
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = WHITE }, { .color = ORANGE } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = WHITE },
    // Left
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = ORANGE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = ORANGE },
    // Right
    { .colors = {
        { { .color = UNSET }, { .color = WHITE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = RED },
};
Face white_cross_expected_5[6] = {
    // Front
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = GREEN }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = GREEN },
    // Back
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = BLUE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = BLUE },
    // Down
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = YELLOW }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = YELLOW },
    // Up
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = WHITE }, { .color = WHITE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = WHITE },
    // Left
    { .colors = {
        { { .color = UNSET }, { .color = ORANGE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = ORANGE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = ORANGE },
    // Right
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = RED },
};

Face white_cross_base_5_bis[6] = {
    // Front
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = GREEN }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = GREEN },
    // Back
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = BLUE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = BLUE },
    // Down
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = YELLOW }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = YELLOW },
    // Up
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = RED }, { .color = WHITE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = WHITE },
    // Left
    { .colors = {
        { { .color = UNSET }, { .color = WHITE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = ORANGE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = ORANGE },
    // Right
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = RED },
};
Face white_cross_expected_5_bis[6] = {
    // Front
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = GREEN }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = GREEN },
    // Back
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = BLUE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = BLUE },
    // Down
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = YELLOW }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = YELLOW },
    // Up
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = WHITE }, { .color = WHITE } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = WHITE },
    // Left
    { .colors = {
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
        { { .color = UNSET }, { .color = ORANGE }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = ORANGE },
    // Right
    { .colors = {
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
        { { .color = UNSET }, { .color = RED }, { .color = UNSET } },
        { { .color = UNSET }, { .color = UNSET }, { .color = UNSET } },
    }, .main_color = RED },
};

bool expect_result(Face faces[6], Face expected[6]) {
    for (int face = 0; face < 6; face++) {
        if (faces[face].main_color != expected[face].main_color)
            return false;

        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                // Unset is the "wild" card.
                if (faces[face].colors[row][col].color == UNSET || expected[face].colors[row][col].color == UNSET)
                    continue;
                if (faces[face].colors[row][col].color != expected[face].colors[row][col].color)
                    return false;
            }
        }
    }
    return true;
}

bool test_moves(Face faces[6]) {
    bool result;

    create_cube(faces);
    run_move("L' R' R' D R' L' F' B B D F L' L R U' F R' L L' U D R L U B' B' B", faces);
    result = expect_result(faces, move_expected_1);
    if (!result)
        return false;

    create_cube(faces);
    run_move("U D' B D U' L' F R' D B D B F' R' U' U L' U", faces);
    result = expect_result(faces, move_expected_2);
    if (!result)
        return false;

    create_cube(faces);
    run_move("B D' R' D B U D' U D' B F' L' F' L L B L D U L' D U U R' R' U F L' B'", faces);
    result = expect_result(faces, move_expected_3);
    return result;
}

bool test_white_cross(Face faces[6]) {
    bool result;

    faces = white_cross_base_1;
    make_perfect_white_cross(faces);
    result = expect_result(faces, perfect_white_cross_expected);
    if (!result)
        return false;

    faces = white_cross_base_2;
    make_perfect_white_cross(faces);
    result = expect_result(faces, perfect_white_cross_expected);
    if (!result)
        return false;

    faces = white_cross_base_3;
    make_perfect_white_cross(faces);
    result = expect_result(faces, perfect_white_cross_expected);
    if (!result)
        return false;

    faces = white_cross_base_3_bis;
    make_perfect_white_cross(faces);
    result = expect_result(faces, perfect_white_cross_expected);
    if (!result)
        return false;

    faces = white_cross_base_4;
    make_perfect_white_cross(faces);
    result = expect_result(faces, white_cross_expected_4);
    if (!result)
        return false;

    faces = white_cross_base_5;
    make_perfect_white_cross(faces);
    result = expect_result(faces, white_cross_expected_5);
    if (!result)
        return false;

    faces = white_cross_base_5_bis;
    make_perfect_white_cross(faces);
    result = expect_result(faces, white_cross_expected_5_bis);
    return result;
}

bool test_many(Face faces[6]) {
    bool result;

    result = test_moves(faces);
    if (!result)
        return false;

    create_cube(faces);
    result = test_white_cross(faces);
    if (!result)
        return false;

    return result;
}

