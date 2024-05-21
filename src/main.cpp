#include "raylib.h"

#define WIDTH 400
#define HEIGHT WIDTH


void update_camera(Camera *cam)
{
   Vector3 rot = { 0, 0, 0 };
   Vector3 move = { 0, 0, 0 };

   rot.x = IsKeyDown(KEY_A) * 0.1 - IsKeyDown(KEY_D) * 0.1;
   rot.y = IsKeyDown(KEY_W) * 0.1 - IsKeyDown(KEY_S) * 0.1;

   float zoom = GetMouseWheelMove() * -0.5;

   UpdateCameraPro(cam, move, rot, zoom);
}


int main()
{
   // TODO: remember to change the title :)
   InitWindow(WIDTH, HEIGHT, "title");

   Camera camera;
   camera.projection = CAMERA_PERSPECTIVE;
   camera.position = (Vector3){ 0, 2, 4 };   
   camera.target = (Vector3){ 0, 2, 0 };     
   camera.up = (Vector3){ 0, 1, 0 };         
   camera.fovy = 60.0f;                            
   
   while ( !WindowShouldClose() ) {
   
      update_camera(&camera);
      
      BeginDrawing();
      ClearBackground(RAYWHITE);
         BeginMode3D(camera);
                                                                                 //
         DrawCube(camera.target, 0.5f, 0.5f, 0.5f, PURPLE);
         DrawCubeWires(camera.target, 0.5f, 0.5f, 0.5f, DARKPURPLE);

         EndMode3D();
      EndDrawing();
   }

   CloseWindow();
   
   return 0;
}
