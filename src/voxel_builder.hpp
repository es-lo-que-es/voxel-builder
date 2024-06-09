#ifndef VOXEL_BUILDER_HEADER_HPP
#define VOXEL_BUILDER_HEADER_HPP

#include "voxel.hpp"
#include "voxel_picker.hpp"
#include "color_picker.hpp"


struct VoxelBuilder {

   Voxels voxels;
   Camera camera;

   ColorPicker color_picker;
   VoxelPicker voxel_picker;

   explicit VoxelBuilder(float size);

   void remove_voxel(Vector3 index);
   void add_voxel(Vector3 index);

   void draw() const;
   void update();

   void run();
};


#endif
