#include "voxel_builder.hpp"
#include "config.hpp"

#include <emscripten.h>
#include <emscripten/html5.h>

VoxelBuilder app(VOXEL_SPACE_SIZE);


EM_BOOL animation_frame(double time, void * par)
{
   app.update();
   app.draw();

   // request another frame to keep a loop going
   emscripten_request_animation_frame(&animation_frame, nullptr);

   return EM_TRUE;
}



int main()
{
   InitWindow(WIDTH, HEIGHT, "voxel-builder");
   SetExitKey(KEY_NULL); 

   SetTargetFPS(30);
   emscripten_request_animation_frame(&animation_frame, nullptr);
   
   return 0;
}
