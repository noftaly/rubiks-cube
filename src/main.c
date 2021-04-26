#include <stdio.h>
#include <string.h>
#include "rubiks.h"

int main() {
    create_cube();
    display_cube();
    char input[100];

    while (strcmp(input, "end") != 0) {
        scanf("%s", input);
        if (strcmp(input, "reset") == 0)
            create_cube();
        else
            run_move(input);
        display_cube();
    }

    display_cube();
    free_cube();

    return 0;
}
