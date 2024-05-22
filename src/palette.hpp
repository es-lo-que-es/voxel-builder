#ifndef PALETTE_HEADER_HPP
#define PALETTE_HEADER_HPP

#include <vector>
#include "raylib.h"


const std::vector<Color> default_palette = { 
   { 0, 0, 0, 0 },
   { 140, 70, 70, 255 },
}; 

struct Palette {

   std::vector<Color> colors = default_palette;

   Color get(size_t index) const {
      return colors[index % colors.size()];
   }
};


#endif
