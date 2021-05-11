#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "rubiks.h"

int main() {
    srand(time(NULL));

    Face faces[6];
    create_cube(faces);
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
        /*else if (strcmp(input, "white cross")==0)
            make_white_cross()*/
        else
            run_move(input, faces);
        display_cube(faces);
    }
    return 0;
}
