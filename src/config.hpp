#ifndef CONFIG_HEADER_HPP
#define CONFIG_HEADER_HPP

#include "raylib.h"

#define WIDTH 600.0f
#define COLOR_PICKER_SIZE 30.0f

#define HEIGHT WIDTH
#define VOXEL_SPACE_SIZE 16.0f

const Color GRID_COLOR = { 197, 209, 222, 40 };
const Color HELP_COLOR = { 100, 200, 100, 255 };
const Color BACKGROUND = { 28, 33, 40, 255 };
const Color WIRE_COLOR = { 197, 209, 222, 50 };

const Vector2 COLOR_PICKER_POS = { WIDTH - COLOR_PICKER_SIZE, 0 };

#define HELP_FONT_SIZE 20
const Vector2 HELP_POS = { HELP_FONT_SIZE, HEIGHT - HELP_FONT_SIZE * 3 };

#define TARGET_FPS 30


const Color PALETTE_COLORS[] = {
   { 0, 0, 0, 0 },
   { 45, 45, 45, 255 },  // Soft Dark Gray
   { 85, 85, 85, 255 },  // Dimmed Medium Gray
   { 70, 70, 90, 255 },  // Dimmed Soft Blue Gray
   { 60, 50, 70, 255 },  // Dimmed Soft Purple Gray
   { 50, 60, 70, 255 },  // Dimmed Soft Teal Gray
   { 40, 60, 50, 255 },  // Dimmed Soft Green Gray
   { 50, 40, 40, 255 },  // Dimmed Soft Reddish Brown
   { 70, 60, 40, 255 },  // Dimmed Soft Olive Gray
};

#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
const size_t PALETTE_SIZE = COUNT_OF(PALETTE_COLORS);


#define UPDATE_DELAY 0.080

#endif
