#ifndef PALETTE_HEADER_HPP
#define PALETTE_HEADER_HPP

#include <vector>
#include "raylib.h"


const std::vector<Color> default_colors = { 
   { 0, 0, 0, 0 },
   {255, 182, 193, 255}, // Light Pink
   {176, 224, 230, 255}, // Powder Blue
   {250, 235, 215, 255}, // Antique White
   {152, 251, 152, 255}, // Pale Green
   {255, 239, 213, 255}, // Papaya Whip
   {221, 160, 221, 255}, // Plum
   {255, 228, 196, 255}, // Bisque
   {240, 230, 140, 255}, // Khaki
   {255, 222, 173, 255}, // Navajo White
   {230, 230, 250, 255}  // Lavender
}; 

struct Palette {

   std::vector<Color> colors = default_colors;
   Color get(size_t index) const;

};


#endif
