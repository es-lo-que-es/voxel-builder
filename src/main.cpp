#include "time.h"
#include "stdlib.h"

#include "camera.hpp"
#include "voxel.hpp"
#include "grid.hpp"
#include <cstdio>
#include <raylib.h>
#include "voxel_picker.hpp"


#define WIDTH 400
#define HEIGHT WIDTH

#include <chrono>


std::chrono::time_point<std::chrono::high_resolution_clock> start;


void start_timer()
{
   start = std::chrono::high_resolution_clock::now();
}


void end_timer(const char * str)
{
   auto end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double, std::milli> duration = end - start;

   printf("%s: %lfms\n", str, duration.count());
}





struct VoxelBuilder {

   explicit VoxelBuilder(int size);

   VoxelPicker picker;
   Camera camera;
   Voxels voxels;
};


VoxelBuilder::VoxelBuilder(int size)
   : voxels(16)
{
   init_camera(&camera, { 16, 16, 16 });
   
   voxels[{8, 0, 8}] = 1;
   voxels[{8, 1, 8}] = 1;
   voxels[{8, 2, 8}] = 1;
   voxels[{8, 3, 8}] = 1;
   voxels[{8, 4, 8}] = 1;

   voxels[{0, 0, 0}] = 1;
   voxels[{0, 1, 0}] = 1;
   voxels[{0, 2, 0}] = 1;
   voxels[{0, 3, 0}] = 1;
   voxels[{0, 4, 0}] = 1;

   voxels[{15, 0, 15}] = 1;
   voxels[{15, 1, 15}] = 1;
   voxels[{15, 2, 15}] = 1;
   voxels[{15, 3, 15}] = 1;
   voxels[{15, 4, 15}] = 1;
}


void draw_cube_at(Vector3 p, Color col)
{
   p = { p.x + 0.5f, p.y + 0.5f, p.z+0.5f };
   DrawCubeWiresV(p, {1, 1, 1}, col);
}


int main()
{
   srand(time(0));
   // TODO: remember to change the title :)
   InitWindow(WIDTH, HEIGHT, "title");

   VoxelBuilder app(16);


   SetTargetFPS(60);

   while ( !WindowShouldClose() ) {
   
      update_camera(&app.camera);

      if ( IsMouseButtonReleased(MOUSE_BUTTON_LEFT) ) 
         app.picker.update(&app.voxels, app.camera);
   
      BeginDrawing();
      ClearBackground(RAYWHITE);

         BeginMode3D(app.camera);
         draw_grid(app.camera.position, 16);
         app.voxels.draw();

         if ( app.picker.selected ) {
            draw_cube_at(app.picker.remove_position, WHITE);
            draw_cube_at(app.picker.add_position, GREEN);
         }
            
         EndMode3D();

      //DrawText(TextFormat("pos: %0.2f, %0.2f %0.2f", pos.x, pos.y, pos.z), 10, 40, 20, BLACK);
      DrawFPS(10, 10);
      EndDrawing();
   }

   CloseWindow();
   
   return 0;
}
