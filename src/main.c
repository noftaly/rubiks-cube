#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rubiks.h"

int main() {
    srand(time(NULL));

    Face faces[6] = {
        { .colors = {
            { { .color = ORANGE }, { .color = GREEN }, { .color = YELLOW } },
            { { .color = RED }, { .color = GREEN }, { .color = GREEN } },
            { { .color = RED }, { .color = BLUE }, { .color = WHITE } },
        } },
        { .colors = {
            { { .color = ORANGE }, { .color = BLUE }, { .color = RED } },
            { { .color = BLUE }, { .color = BLUE }, { .color = YELLOW } },
            { { .color = YELLOW }, { .color = ORANGE }, { .color = RED } },
        } },
        { .colors = {
            { { .color = GREEN }, { .color = ORANGE }, { .color = BLUE } },
            { { .color = GREEN }, { .color = YELLOW }, { .color = GREEN } },
            { { .color = BLUE }, { .color = YELLOW }, { .color = ORANGE } },
        } },
        { .colors = {
            { { .color = YELLOW }, { .color = WHITE }, { .color = BLUE } },
            { { .color = WHITE }, { .color = WHITE }, { .color = WHITE } },
            { { .color = GREEN }, { .color = WHITE }, { .color = RED } },
        } },
        { .colors = {
            { { .color = GREEN }, { .color = ORANGE }, { .color = WHITE } },
            { { .color = RED }, { .color = ORANGE }, { .color = BLUE } },
            { { .color = WHITE }, { .color = RED }, { .color = WHITE } },
        } },
        { .colors = {
            { { .color = BLUE }, { .color = RED }, { .color = YELLOW } },
            { { .color = YELLOW }, { .color = RED }, { .color = YELLOW } },
            { { .color = ORANGE }, { .color = ORANGE }, { .color = GREEN } },
        } },
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
        else if (strcmp(input, "place_corner")==0)
            place_corners(faces);
        else if (strcmp(input, "yellowcross")==0)
            make_yellow_cross(faces);

        else
            run_move(input, faces);
        display_cube(faces);
    }
    return 0;
}
