#include "voxel_builder.hpp"
#include "config.hpp"


int main()
{
   InitWindow(WIDTH, HEIGHT, "voxel-builder");

   SetExitKey(KEY_NULL); 
   SetTargetFPS(TARGET_FPS);
   
   VoxelBuilder app(VOXEL_SPACE_SIZE);
   app.run();

   CloseWindow();
   
   return 0;
}
