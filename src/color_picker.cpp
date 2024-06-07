#include "color_picker.hpp"
#include "raymath.h"
#include "stdio.h"


ColorPicker::ColorPicker(Vector2 pos, float size)
{
   rect = { pos.x, pos.y, size, size };

   bounding_rect = rect;
   bounding_rect.height = rect.height * (palette.colors.size() - 1);
}


Color ColorPicker::get() const
{
   return palette.get(selected_index);
}


void ColorPicker::draw() const
{
   int size = palette.colors.size();

   float r = rect.width / 2;
   Vector2 c = { rect.x + r, rect.y + r };

   // draw selected first
   Vector2 sel = { c.x, c.y + rect.height * (selected_index - 1) };
   DrawCircleV(sel, r, BLACK);

   // padding
   float draw_rad = r - 4;

   for ( int i = 1; i < size; ++i ) {
      DrawCircleV(c, draw_rad+1, BLACK);
      DrawCircleV(c, draw_rad, palette.get(i));
      c.y = c.y + rect.height;
   }
}


void ColorPicker::update()
{
   updated = false;

   if ( !IsMouseButtonDown(MOUSE_BUTTON_LEFT) ) return;

   Vector2 mouse_pos = GetMousePosition();
   if ( !CheckCollisionPointRec(mouse_pos, bounding_rect) ) return;

   float y = mouse_pos.y - rect.y;
   selected_index = (int)(y / rect.height) + 1;

   updated = true;
}
