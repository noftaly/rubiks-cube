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
            { { .color = RED }, { .color = GREEN }, { .color = WHITE } },
            { { .color = BLUE }, { .color = GREEN }, { .color = GREEN } },
            { { .color = BLUE }, { .color = YELLOW }, { .color = ORANGE } },
        }, .main_color = GREEN },
        // Back
        { .colors = {
            { { .color = RED }, { .color = BLUE }, { .color = WHITE } },
            { { .color = ORANGE }, { .color = BLUE }, { .color = YELLOW } },
            { { .color = GREEN }, { .color = ORANGE }, { .color = RED } },
        }, .main_color = BLUE },
        // Down
        { .colors = {
            { { .color = RED }, { .color = ORANGE }, { .color = BLUE } },
            { { .color = GREEN }, { .color = YELLOW }, { .color = BLUE } },
            { { .color = GREEN }, { .color = BLUE }, { .color = YELLOW } },
        }, .main_color = YELLOW },
        // Up
        { .colors = {
            { { .color = GREEN }, { .color = WHITE }, { .color = YELLOW } },
            { { .color = WHITE }, { .color = WHITE }, { .color = WHITE } },
            { { .color = WHITE }, { .color = WHITE }, { .color = ORANGE } },
        }, .main_color = WHITE },
        // Left
        { .colors = {
            { { .color = ORANGE }, { .color = ORANGE }, { .color = GREEN } },
            { { .color = RED }, { .color = ORANGE }, { .color = YELLOW } },
            { { .color = YELLOW }, { .color = YELLOW }, { .color = WHITE } },
        }, .main_color = ORANGE },
        // Right
        { .colors = {
            { { .color = BLUE }, { .color = RED }, { .color = BLUE } },
            { { .color = RED }, { .color = RED }, { .color = GREEN } },
            { { .color = YELLOW }, { .color = RED }, { .color = ORANGE } },
        }, .main_color = RED },
    };
    // Face faces[6];
    // create_cube(faces);
    display_cube(faces);
    char input[100];

    while (strcmp(input, "end") != 0) {
        puts("Enter what to do: '\e[1;93mreset\e[0m', '\e[1;93mblank\e[0m', '\e[1;93mdefine\e[0m', '\e[1;93mscramble\e[0m', '\e[1;93msolve\e[0m', '\e[1;93mhelp\e[0m' or a valid \e[1;93mmove/sequence\e[0m of moves.");
        printf("\e[0;90m> ");
        scanf("%s", input);
        printf("\e[0m");
        if (strcmp(input, "reset") == 0)
            create_cube(faces);
        else if (strcmp(input, "blank") == 0)
            blank_cube(faces);
        else if (strcmp(input, "define") == 0)
            define_cube(faces);
        else if (strcmp(input, "scramble") == 0)
            scramble_cube(faces);
        else if (strcmp(input, "solve") == 0)
            solve_cube(faces);
        else if (strcmp(input, "help") == 0)
            display_help(faces);
        else
            run_move(input, faces);
        display_cube(faces);
    }
    return 0;
}
