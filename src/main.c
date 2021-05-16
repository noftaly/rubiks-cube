#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rubiks.h"

int main() {
    srand(time(NULL));

    Face faces[6] = {
        // Front
        { .colors = {
            { { .color = YELLOW }, { .color = RED }, { .color = BLUE } },
            { { .color = GREEN }, { .color = GREEN }, { .color = RED } },
            { { .color = RED }, { .color = GREEN }, { .color = BLUE } },
        }, .main_color = GREEN },
        // Back
        { .colors = {
            { { .color = BLUE }, { .color = YELLOW }, { .color = GREEN } },
            { { .color = GREEN }, { .color = BLUE }, { .color = BLUE } },
            { { .color = ORANGE }, { .color = ORANGE }, { .color = ORANGE } },
        }, .main_color = BLUE },
        // Down
        { .colors = {
            { { .color = RED }, { .color = YELLOW }, { .color = ORANGE } },
            { { .color = YELLOW }, { .color = YELLOW }, { .color = GREEN } },
            { { .color = GREEN }, { .color = YELLOW }, { .color = YELLOW } },
        }, .main_color = YELLOW },
        // Up
        { .colors = {
            { { .color = WHITE }, { .color = WHITE }, { .color = WHITE } },
            { { .color = WHITE }, { .color = WHITE }, { .color = WHITE } },
            { { .color = WHITE }, { .color = WHITE }, { .color = WHITE } },
        }, .main_color = WHITE },
        // Left
        { .colors = {
            { { .color = ORANGE }, { .color = ORANGE }, { .color = ORANGE } },
            { { .color = RED }, { .color = ORANGE }, { .color = ORANGE } },
            { { .color = BLUE }, { .color = YELLOW }, { .color = YELLOW } },
        }, .main_color = ORANGE },
        // Right
        { .colors = {
            { { .color = RED }, { .color = RED }, { .color = RED } },
            { { .color = ORANGE }, { .color = RED }, { .color = BLUE } },
            { { .color = ORANGE }, { .color = BLUE }, { .color = RED } },
        }, .main_color = RED },
    };

    // Face faces[6];
    // create_cube(faces);
    display_cube(faces);
    char input[100];

    while (strcmp(input, "end") != 0) {
        puts("Enter what to do: 'reset', 'define', 'scramble', 'solve' or a valid move/sequence of move.");
        scanf("%s", input);
        if (strcmp(input, "reset") == 0)
            create_cube(faces);
        else if (strcmp(input, "define") == 0)
            define_cube(faces);
        else if (strcmp(input, "scramble") == 0)
            scramble_cube(faces);
        else if (strcmp(input, "solve") == 0)
            solve_cube();
        else if (strcmp(input, "wc")==0)
            make_white_cross(faces);
        else
            run_move(input, faces);
        display_cube(faces);
    }
    return 0;
}
