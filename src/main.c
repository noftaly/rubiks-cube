#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rubiks.h"
#include "cube_tester.h"

int main() {
    srand(time(NULL));

   Face faces[6] = {
        { .colors = {
            { { .color = YELLOW }, { .color = GREEN }, { .color = GREEN } },
            { { .color = GREEN }, { .color = GREEN }, { .color = YELLOW } },
            { { .color = WHITE }, { .color = YELLOW }, { .color = YELLOW } },
        }, .main_color = GREEN },
        { .colors = {
            { { .color = BLUE }, { .color = BLUE }, { .color = BLUE } },
            { { .color = YELLOW }, { .color = BLUE }, { .color = ORANGE } },
            { { .color = GREEN }, { .color = BLUE }, { .color = WHITE } },
        }, .main_color = BLUE },
        { .colors = {
            { { .color = BLUE }, { .color = BLUE }, { .color = ORANGE } },
            { { .color = GREEN }, { .color = YELLOW }, { .color = RED } },
            { { .color = GREEN }, { .color = ORANGE }, { .color = RED } },
        }, .main_color = YELLOW },
        { .colors = {
            { { .color = WHITE }, { .color = WHITE }, { .color = RED } },
            { { .color = WHITE }, { .color = WHITE }, { .color = WHITE } },
            { { .color = GREEN }, { .color = WHITE }, { .color = ORANGE } },
        }, .main_color = WHITE },
        { .colors = {
            { { .color = ORANGE }, { .color = ORANGE }, { .color = ORANGE } },
            { { .color = YELLOW }, { .color = ORANGE }, { .color = RED } },
            { { .color = RED }, { .color = ORANGE }, { .color = RED } },
        }, .main_color = ORANGE },
        { .colors = {
            { { .color = WHITE }, { .color = RED }, { .color = YELLOW } },
            { { .color = GREEN }, { .color = RED }, { .color = RED } },
            { { .color = BLUE }, { .color = BLUE }, { .color = YELLOW } },
        }, .main_color = RED },
    };

    // Face faces[6];
    // create_cube(faces);
    display_cube(faces);
    char input[100];

    while (strcmp(input, "end") != 0) {
        puts("Enter what to do: 'reset', 'define', 'scramble', 'solve', 'test' or a valid move/sequence of move.");
        scanf("%s", input);
        if (strcmp(input, "reset") == 0)
            create_cube(faces);
        else if (strcmp(input, "define") == 0)
            define_cube(faces);
        else if (strcmp(input, "scramble") == 0)
            scramble_cube(faces);
        else if (strcmp(input, "solve") == 0)
            solve_cube(faces);
        else if (strcmp(input, "test") == 0)
            printf("Test result: %s\n", test_many(faces) ? "success" : "failed");
        else
            run_move(input, faces);
        display_cube(faces);
    }
    return 0;
}
