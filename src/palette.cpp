#include "palette.hpp"


Color Palette::get(size_t index) const
{
   return colors[index % colors.size()];
}

