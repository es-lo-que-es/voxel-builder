#include "raylib.h"
#include "stdlib.h"
#include "camera.hpp"
#include "voxel.hpp"
#include "time.h"

#define WIDTH 400
#define HEIGHT WIDTH


int main()
{
   srand(time(0));
   // TODO: remember to change the title :)
   InitWindow(WIDTH, HEIGHT, "title");

   Camera camera;
   camera.projection = CAMERA_PERSPECTIVE;
   camera.position = (Vector3){ 16, 16, 16 };   
   camera.target = (Vector3){ 8, 0, 8 };     
   camera.up = (Vector3){ 0, 1, 0 };         
   camera.fovy = 45;                            
   
   Voxel vox(16);
   vox[{0, 0, 0}] = 1;
   vox[{0, 2, 3}] = 1;
   vox[{0, 5, 0}] = 1;
   vox[{1, 0, 4}] = 1;
   vox[{15, 0, 15}] = 1;

   DisableCursor();
   SetTargetFPS(60);


   while ( !WindowShouldClose() ) {
   
      update_camera(&camera);
      
      BeginDrawing();
      ClearBackground(RAYWHITE);
         BeginMode3D(camera);
                                                                                 //
         vox.draw();

         EndMode3D();

      //DrawText(TextFormat("angle: %0.4f", CAMERA_ANGLE), 10, 40, 20, BLACK);
      DrawFPS(10, 10);

      EndDrawing();
   }

   CloseWindow();
   
   return 0;
}
