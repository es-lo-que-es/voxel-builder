#include "time.h"
#include "stdlib.h"

#include "camera.hpp"
#include "voxel.hpp"
#include "grid.hpp"
#include <cmath>
#include <cstdio>
#include <raylib.h>
#include "raymath.h"

#define WIDTH 400
#define HEIGHT WIDTH

#include <stdio.h>
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


struct VoxelPicker {
   
   void update(Voxels * vox, Camera cam);
   void entry_collision(Camera cam, float size);
   void exit_collision(float size);

   Vector3 selected_pos;
   bool selected;

   RayCollision collision;
   Ray ray;
};


Vector3 rotate_vec(Vector3 vec, Vector3 angle)
{
   Matrix m = MatrixRotateXYZ(angle);
   return Vector3Transform(vec, m);
}



void VoxelPicker::exit_collision(float s)
{
   float distance = s * 2;
   Vector3 p = collision.point;

   float x = p.x + distance * ray.direction.x;
   float y = p.y + distance * ray.direction.y;
   float z = p.z + distance * ray.direction.z;

   ray.direction = Vector3Negate(ray.direction);
   ray.position = { x, y, z };

   collision = GetRayCollisionBox(ray, {{0, 0, 0}, {s, s, s}});
}


void VoxelPicker::entry_collision(Camera cam, float s)
{
   ray = GetMouseRay(GetMousePosition(), cam);
   collision = GetRayCollisionBox(ray, {{0, 0, 0}, {s, s, s}});
}


void VoxelPicker::update(Voxels * vox, Camera cam)
{
   float size = vox->data.size();
   entry_collision(cam, size);

   Vector3 p = collision.point;
   selected = collision.hit;

   if ( !selected ) return;
   exit_collision(size);

   Vector3 exit = collision.point;

   selected_pos = { floorf(exit.x), floorf(exit.y), floorf(exit.z) };
   printf("dir: %2.2f, %2.2f, %2.2f\n", ray.direction.x, ray.direction.y, ray.direction.z);
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
   
   /*
   voxels[{0, 0, 0}] = 1;
   voxels[{0, 2, 3}] = 1;
   voxels[{0, 5, 0}] = 1;
   voxels[{1, 0, 4}] = 1;
   voxels[{15, 0, 15}] = 1;
   */
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
   
      //start_timer();
      Vector3 v = app.picker.selected_pos;
      //printf("v.x: %2.2f, v.y: %2.2f, v.z: %2.2f\n", v.x, v.y, v.z);
      //end_timer("branching one\n");

      BeginDrawing();
      ClearBackground(RAYWHITE);

         BeginMode3D(app.camera);
         // TODO: move this out of draw
         draw_grid(app.camera.position, 16);
         app.voxels.draw();

         Vector3 p = app.picker.selected_pos;
         p = { p.x + 0.5f, p.y + 0.5f, p.z+0.5f };
         if ( app.picker.selected ) DrawCubeWiresV(p, {1, 1, 1}, GREEN);
         
         DrawRay(app.picker.ray, RED);


         EndMode3D();

      //DrawText(TextFormat("pos: %0.2f, %0.2f %0.2f", pos.x, pos.y, pos.z), 10, 40, 20, BLACK);
      DrawFPS(10, 10);
      EndDrawing();
   }

   CloseWindow();
   
   return 0;
}
