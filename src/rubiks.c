#include <stdio.h>
#include "rubiks.h"

// Rubik* create_rubiks() {}

void display_cube(Rubik* rubiks_cube) {
    printf("       %d %d %d\n", rubiks_cube[0].grid[0][0], rubiks_cube[0].grid[0][1], rubiks_cube[0].grid[0][2]);
    printf("       %d %d %d\n", 1, 2, 3);
    printf("       %d %d %d\n", 1, 2, 3);
    printf("%d %d %d  %d %d %d  %d %d %d  %d %d %d\n", 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3);
    printf("%d %d %d  %d %d %d  %d %d %d  %d %d %d\n", 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3);
    printf("%d %d %d  %d %d %d  %d %d %d  %d %d %d\n", 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3);
    printf("       %d %d %d\n", 1, 2, 3);
    printf("       %d %d %d\n", 1, 2, 3);
    printf("       %d %d %d\n", 1, 2, 3);
}
