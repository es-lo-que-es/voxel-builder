#ifndef VOXEL_PICKER_HEADER_HPP
#define VOXEL_PICKER_HEADER_HPP

#include "voxel.hpp"
#include <raylib.h>
#include <vector>


struct VoxelPicker {
   
   void update(Voxels * vox, Camera cam);

   void DDA(Voxels * vox, Vector3 s, Vector3 e, Vector3 dir);
   void entry_collision(Camera cam, float size);
   void exit_collision(float size);

   std::vector<Vector3> trace;
   Vector3 selected_pos;
   bool selected;

   RayCollision collision;
   Ray ray;
};


#endif
