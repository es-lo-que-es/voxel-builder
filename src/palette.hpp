#ifndef PALETTE_HEADER_HPP
#define PALETTE_HEADER_HPP

#include <vector>
#include "raylib.h"


struct Palette {

   std::vector<Color> colors;
   Color get(size_t index) const;

   Palette();

};


#endif
