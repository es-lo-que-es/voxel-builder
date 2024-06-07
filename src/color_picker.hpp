#ifndef COLOR_PICKER_HEADER_HPP
#define COLOR_PICKER_HEADER_HPP

#include "palette.hpp"


struct ColorPicker {

   bool updated;

   Rectangle bounding_rect;
   Rectangle rect;

   Palette palette;
   int selected_index = 1;

   ColorPicker(Vector2 pos, float size);
   Color get() const;

   void draw() const;
   void update();

};

#endif
