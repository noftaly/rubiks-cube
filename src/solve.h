#pragma once

#include <stdbool.h>
#include "rubiks.h"

bool has_white_cross(Face[6]);
bool has_white_face(Face[6]);
bool has_crown(Face[6]);
bool has_yellow_cross(Face[6]);
bool has_perfect_white_cross(Face[6]);
bool has_perfect_yellow_cross(Face[6]);
bool has_white_edge_on_down(Face[6]);
bool includes(Color[3], Color);

int get_next_face(int index);
int get_previous_face(int index);

void make_white_cross(Face[6]);
void place_white_edges(Face[6]);
void place_white_corners(Face[6]);
void solve_crown(Face[6]);
void make_yellow_cross(Face[6]);
void place_yellow_edges(Face[6]);
void place_yellow_corners(Face[6]);
void solve_yellow_corners(Face[6]);
