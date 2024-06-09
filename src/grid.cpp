#include "grid.hpp"
#include "raymath.h"
#include "config.hpp"

void draw_lines(Vector3 s, Vector3 e, Vector3 m, int count)
{
   for ( int i = 0; i <= count; ++i ) {

      DrawLine3D(s, e, GRID_COLOR);

      s = Vector3Add(s, m);
      e = Vector3Add(e, m);
   }
}


void draw_grid(Vector3 camera_pos,  float c, GridOption option)
{
   if ( option == None ) return;
   Vector3 pos = Vector3Subtract(camera_pos, {c , c, c});

   draw_lines({0, 0, 0}, {0, 0, c}, {1, 0, 0}, c);
   draw_lines({0, 0, 0}, {c, 0, 0}, {0, 0, 1}, c);
   if ( option == Floor ) return;
   
   // x-wall
   if ( pos.x > 0 ) {
      draw_lines({0, 0, 0}, {0, c, 0}, {0, 0, 1}, c);
      draw_lines({0, 0, 0}, {0, 0, c}, {0, 1, 0}, c);
   } else {
      draw_lines({c, 0, 0}, {c, c, 0}, {0, 0, 1}, c);
      draw_lines({c, 0, 0}, {c, 0, c}, {0, 1, 0}, c);
   }

   // z-wall
   if ( pos.z > 0 ) {
      draw_lines({0, 0, 0}, {0, c, 0}, {1, 0, 0}, c);
      draw_lines({0, 0, 0}, {c, 0, 0}, {0, 1, 0}, c);
   } else {
      draw_lines({0, 0, c}, {0, c, c}, {1, 0, 0}, c);
      draw_lines({0, 0, c}, {c, 0, c}, {0, 1, 0}, c);
   }
}
