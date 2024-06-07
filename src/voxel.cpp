#include "voxel.hpp"
#include "stdlib.h"
#include <cassert>
#include <cstdint>


const Color wire_col = { 140, 140, 140, 255 };


Color random_color()
{
   uint8_t r = rand() % 256;
   uint8_t g = rand() % 256;
   uint8_t b = rand() % 256;

   return { r, g, b, 255 };
}


Voxels::Voxels(size_t size)
{
   data.resize(size);

   for ( auto &y : data ) {
      y.resize(size);
      for ( auto &z : y ) {
         z.resize(size);
      }
   }
}


char& Voxels::operator[] (Vector3 p) 
{
   assert(p.x >= 0 and p.x < data.size());
   assert(p.y >= 0 and p.y < data.size());
   assert(p.z >= 0 and p.z < data.size());

   return data[p.x][p.y][p.z];
}


void Voxels::draw_voxels(const Palette * palette) const
{
   float o = 0.5;
   Vector3 size = { 1, 1, 1 };

   for ( int i = 0; i < data.size(); ++i ) {

      for ( int j = 0; j < data[i].size(); ++j ) {

         for ( int k = 0; k < data[j].size(); ++k ) {

            if ( data[i][j][k] == 0 ) continue;

            Color col = palette->get(data[i][j][k]);
            Vector3 pos = { o+(float)i, o+float(j), o+float(k) };

            DrawCubeWiresV(pos, size, wire_col);
            DrawCubeV(pos, size, col);
         }
      }
   }
}


void Voxels::draw(const Palette * palette) const
{
   draw_voxels(palette);
}


bool Voxels::in_range(Vector3 pos) const
{
   float s = data.size();

   if ( pos.x < 0 || pos.y < 0 || pos.z < 0 ) return false;
   if ( pos.x >= s || pos.y >= s || pos.z >= s ) return false;

   return true;
}
