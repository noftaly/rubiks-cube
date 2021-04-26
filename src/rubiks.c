#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "rubiks.h"

void strswap(char* s, char* t) {
    char* temp = (char*) malloc(strlen(s) + 1);
    strcpy(temp, s);
    strcpy(s, t);
    strcpy(t, temp);
}

void facerotate(char* matrix[3][3]) {
    strswap(matrix[0][0], matrix[0][2]);
    strswap(matrix[0][0], matrix[2][2]);
    strswap(matrix[0][0], matrix[2][0]);
    strswap(matrix[0][1], matrix[1][2]);
    strswap(matrix[0][1], matrix[2][1]);
    strswap(matrix[0][1], matrix[1][0]);
}

void rfacerotate(char* matrix[3][3]) {
    strswap(matrix[0][0], matrix[2][0]);
    strswap(matrix[0][0], matrix[2][2]);
    strswap(matrix[0][0], matrix[0][2]);
    strswap(matrix[0][1], matrix[1][0]);
    strswap(matrix[0][1], matrix[2][1]);
    strswap(matrix[0][1], matrix[1][2]);
}

void strarrswap(char* matrix[3][3], char* rc, char* matrix1[3][3], char* rc1) {
    int cr = *(rc + 1) - '0';
    int cr1 = *(rc1 + 1) - '0';

    if (*rc == 'r') {
        if (*rc1 == 'r') {
            for (int i = 0; i < 3; i++)
                strswap(matrix[cr][i], matrix1[cr1][i]);
        } else if (*rc1 == 'c') {
            for (int i = 0; i < 3; i++)
                strswap(matrix[cr][i], matrix1[i][cr1]);
        }
    } else if (*rc == 'c') {
        if (*rc1 == 'c') {
            for (int i = 0; i < 3; i++)
                strswap(matrix[i][cr], matrix1[i][cr1]);
        } else if (*rc1 == 'r') {
            for (int i = 0; i < 3; i++)
                strswap(matrix[i][cr], matrix1[cr1][i]);
        }
    }
}

void rotate_front() {
    strswap(left.color[0][2], left.color[2][2]);
    strswap(right.color[0][0], right.color[2][0]);
    strarrswap(down.color, (char* ) "r0", left.color, (char* ) "c2");
    strarrswap(down.color, (char* ) "r0", up.color, (char* ) "r2");
    strarrswap(down.color, (char* ) "r0", right.color, (char* ) "c0");
    facerotate(front.color);
}

void rotate_right() {
    strarrswap(down.color, (char* ) "c2", front.color, (char* ) "c2");
    strarrswap(down.color, (char* ) "c2", up.color, (char* ) "c2");
    strarrswap(down.color, (char* ) "c2", back.color, (char* ) "c2");
    facerotate(right.color);
}

void rotate_left() {
    strarrswap(down.color, (char* ) "c0", back.color, (char* ) "c0");
    strarrswap(down.color, (char* ) "c0", up.color, (char* ) "c0");
    strarrswap(down.color, (char* ) "c0", front.color, (char* ) "c0");
    facerotate(left.color);
}

void rotate_up() {
    strswap(back.color[2][0], back.color[2][2]);
    strswap(left.color[0][0], left.color[0][2]);
    strarrswap(front.color, (char* ) "r0", left.color, (char* ) "r0");
    strarrswap(front.color, (char* ) "r0", back.color, (char* ) "r2");
    strarrswap(front.color, (char* ) "r0", right.color, (char* ) "r0");
    facerotate(up.color);
}

void rotate_down() {
    strswap(back.color[0][0], back.color[0][2]);
    strswap(right.color[2][0], right.color[2][2]);
    strarrswap(front.color, (char* ) "r2", right.color, (char* ) "r2");
    strarrswap(front.color, (char* ) "r2", back.color, (char* ) "r0");
    strarrswap(front.color, (char* ) "r2", left.color, (char* ) "r2");
    facerotate(down.color);
}

void rotate_back() {
    strswap(up.color[0][0], up.color[0][2]);
    strswap(down.color[2][0], down.color[2][2]);
    strarrswap(down.color, (char* ) "r2", right.color, (char* ) "c2");
    strarrswap(down.color, (char* ) "r2", up.color, (char* ) "r0");
    strarrswap(down.color, (char* ) "r2", left.color, (char* ) "c0");
    rfacerotate(back.color);
}

void rotate_front_reverse() {
    strswap(up.color[2][0], up.color[2][2]);
    strswap(down.color[0][0], down.color[0][2]);
    strarrswap(down.color, (char* ) "r0", right.color, (char* ) "c0");
    strarrswap(down.color, (char* ) "r0", up.color, (char* ) "r2");
    strarrswap(down.color, (char* ) "r0", left.color, (char* ) "c2");
    rfacerotate(front.color);
}

void rotate_right_reverse() {
    strarrswap(down.color, (char* ) "c2", back.color, (char* ) "c2");
    strarrswap(down.color, (char* ) "c2", up.color, (char* ) "c2");
    strarrswap(down.color, (char* ) "c2", front.color, (char* ) "c2");
    rfacerotate(right.color);
}

void rotate_left_reverse() {
    strarrswap(down.color, (char* ) "c0", front.color, (char* ) "c0");
    strarrswap(down.color, (char* ) "c0", up.color, (char* ) "c0");
    strarrswap(down.color, (char* ) "c0", back.color, (char* ) "c0");
    rfacerotate(left.color);
}

void rotate_up_reverse() {
    strswap(back.color[2][0], back.color[2][2]);
    strswap(right.color[0][0], right.color[0][2]);
    strarrswap(front.color, (char* ) "r0", right.color, (char* ) "r0");
    strarrswap(front.color, (char* ) "r0", back.color, (char* ) "r2");
    strarrswap(front.color, (char* ) "r0", left.color, (char* ) "r0");
    rfacerotate(up.color);
}

void rotate_down_reverse() {
    strswap(back.color[0][0], back.color[0][2]);
    strswap(left.color[2][0], left.color[2][2]);
    strarrswap(front.color, (char* ) "r2", left.color, (char* ) "r2");
    strarrswap(front.color, (char* ) "r2", back.color, (char* ) "r0");
    strarrswap(front.color, (char* ) "r2", right.color, (char* ) "r2");
    rfacerotate(down.color);
}

void rotate_back_reverse() {
    strswap(right.color[0][2], right.color[2][2]);
    strswap(left.color[0][0], left.color[2][0]);
    strarrswap(down.color, (char* ) "r2", left.color, (char* ) "c0");
    strarrswap(down.color, (char* ) "r2", up.color, (char* ) "r0");
    strarrswap(down.color, (char* ) "r2", right.color, (char* ) "c2");
    rfacerotate(back.color);
}

void create_face(char* matrix[3][3], char* color) {
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            matrix[r][c] = (char* ) malloc(strlen(color) + 2);
            strcpy(matrix[r][c], color);
        }
    }
}

void free_face(char* matrix[3][3]) {
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c)
            free(matrix[r][c]);
    }
}

void run_move(const char* move) {
    for (int i = 0; move[i] != '\0'; ++i) {
        if (move[i + 1] == '\'') {
            switch (move[i]) {
                case 'R': case 'r':
                    rotate_right_reverse();
                    break;
                case 'L': case 'l':
                    rotate_left_reverse();
                    break;
                case 'U': case 'u':
                    rotate_up_reverse();
                    break;
                case 'D': case 'd':
                    rotate_down_reverse();
                    break;
                case 'F': case 'f':
                    rotate_front_reverse();
                    break;
                case 'B': case 'b':
                    rotate_back_reverse();
                    break;
            }
            i++;
        } else {
            switch (move[i]) {
                case 'R': case 'r':
                    rotate_right();
                    break;
                case 'L': case 'l':
                    rotate_left();
                    break;
                case 'U': case 'u':
                    rotate_up();
                    break;
                case 'D': case 'd':
                    rotate_down();
                    break;
                case 'F': case 'f':
                    rotate_front();
                    break;
                case 'B': case 'b':
                    rotate_back();
                    break;
            }
        }
    }
}

void create_cube() {
    create_face(front.color, (char* ) "G");
    create_face(back.color, (char* ) "B");
    create_face(down.color, (char* ) "W");
    create_face(up.color, (char* ) "Y");
    create_face(left.color, (char* ) "R");
    create_face(right.color, (char* ) "O");
}

void free_cube() {
    free_face(front.color);
    free_face(back.color);
    free_face(down.color);
    free_face(up.color);
    free_face(left.color);
    free_face(right.color);
}

void display_cube() {
    printf("          %s  %s  %s\n", up.color[0][0], up.color[0][1], up.color[0][2]);
    printf("          %s  %s  %s\n", up.color[1][0], up.color[1][1], up.color[1][2]);
    printf("          %s  %s  %s\n", up.color[2][0], up.color[2][1], up.color[2][2]);

    printf("%s  %s  %s   %s  %s  %s   %s  %s  %s   %s  %s  %s\n",
        left.color[0][0], left.color[0][1], left.color[0][2],
        front.color[0][0], front.color[0][1], front.color[0][2],
        right.color[0][0], right.color[0][1], right.color[0][2],
        back.color[0][0], back.color[0][1], back.color[0][2]
    );
    printf("%s  %s  %s   %s  %s  %s   %s  %s  %s   %s  %s  %s\n",
        left.color[1][0], left.color[1][1], left.color[1][2],
        front.color[1][0], front.color[1][1], front.color[1][2],
        right.color[1][0], right.color[1][1], right.color[1][2],
        back.color[1][0], back.color[1][1], back.color[1][2]
    );
    printf("%s  %s  %s   %s  %s  %s   %s  %s  %s   %s  %s  %s\n",
        left.color[2][0], left.color[2][1], left.color[2][2],
        front.color[2][0], front.color[2][1], front.color[2][2],
        right.color[2][0], right.color[2][1], right.color[2][2],
        back.color[2][0], back.color[2][1], back.color[2][2]
    );

    printf("          %s  %s  %s\n", down.color[0][0], down.color[0][1], down.color[0][2]);
    printf("          %s  %s  %s\n", down.color[1][0], down.color[1][1], down.color[1][2]);
    printf("          %s  %s  %s\n", down.color[2][0], down.color[2][1], down.color[2][2]);
}
