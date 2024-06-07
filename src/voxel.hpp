#ifndef VOXEL_HEADER_HPP
#define VOXEL_HEADER_HPP

#include <raylib.h>
#include <vector>
#include "palette.hpp"



struct Voxels {

   std::vector<std::vector<std::vector<char>>> data;

   explicit Voxels(size_t size);

   void draw_voxels(const Palette * palette) const;
   void draw(const Palette * palette) const;

   bool in_range(Vector3 pos) const;
   char& operator[] (Vector3 pos);
   void clear();

};


#endif
