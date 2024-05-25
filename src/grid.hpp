#ifndef GRID_HEADER_HPP
#define GRID_HEADER_HPP

#include "raylib.h"


enum GridOption { Full, Floor, None };
void draw_grid(Vector3 camera_pos,  float count, GridOption option = Floor);

#endif
