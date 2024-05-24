#ifndef VOXEL_HEADER_HPP
#define VOXEL_HEADER_HPP

#include <raylib.h>
#include <vector>
#include "palette.hpp"



struct Voxel {

   void draw() const;
   explicit Voxel(size_t size);

   char& operator[] (Vector3 pos);
   void draw_voxels() const;

   std::vector<std::vector<std::vector<char>>> data;
   Palette palette;

};


#endif
