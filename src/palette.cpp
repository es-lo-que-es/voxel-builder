#include "palette.hpp"
#include "config.hpp"

Palette::Palette()
{
   for ( int i = 0; i < PALETTE_SIZE; ++i ) 
      colors.push_back(PALETTE_COLORS[i]);
}


Color Palette::get(size_t index) const
{
   return colors[index % colors.size()];
}
