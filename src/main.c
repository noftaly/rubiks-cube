#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rubiks.h"

int main() {
    srand(time(NULL));

    create_cube();
    display_cube();
    char input[100];

    while (strcmp(input, "end") != 0) {
        puts("Enter what to do: 'reset', 'define', 'scramble', 'solve' or a valid move/sequence of move.");
        scanf("%s", input);
        if (strcmp(input, "reset") == 0)
            create_cube();
        else if (strcmp(input, "define") == 0)
            define_cube();
        else if (strcmp(input, "scramble") == 0)
            scramble_cube();
        else if (strcmp(input, "solve") == 0)
            solve_cube();
        else
            run_move(input);
        display_cube();
    }

    display_cube();
    free_cube();

    return 0;
}
