#include "voxel.hpp"
#include "stdlib.h"
#include <cstdint>


const Color wire_col = { 140, 140, 140, 255 };


Color random_color()
{
   uint8_t r = rand() % 256;
   uint8_t g = rand() % 256;
   uint8_t b = rand() % 256;

   return { r, g, b, 255 };
}


Voxel::Voxel(size_t size)
{
   data.resize(size);

   for ( auto &y : data ) {
      y.resize(size);
      for ( auto &z : y ) {
         z.resize(size);
      }
   }
}


char& Voxel::operator[] (Vector3 p) 
{
   return data[p.x][p.y][p.z];
}


void Voxel::draw_grid() const
{
   float end = data.size();

   for ( int i = 0; i <= data.size(); ++i ) {
      float v = i;
      DrawLine3D({v, 0, 0}, {v, 0, end}, wire_col);
      DrawLine3D({0, 0, v}, {end, 0, v}, wire_col);
   }
}


void Voxel::draw_voxels() const
{
   float o = 0.5;
   Vector3 size = { 1, 1, 1 };

   for ( int i = 0; i < data.size(); ++i ) {

      for ( int j = 0; j < data[i].size(); ++j ) {

         for ( int k = 0; k < data[j].size(); ++k ) {

            if ( data[i][j][k] == 0 ) continue;

            Color col = palette.get(data[i][j][k]);
            Vector3 pos = { o+(float)i, o+float(j), o+float(k) };

            DrawCubeWiresV(pos, size, wire_col);
            DrawCubeV(pos, size, col);
         }
      }
   }
}


void Voxel::draw() const
{
   draw_grid();
   draw_voxels();
}
