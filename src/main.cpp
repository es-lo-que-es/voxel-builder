#include "camera.hpp"
#include "voxel.hpp"
#include "grid.hpp"
#include "voxel_picker.hpp"


#define WIDTH 400
#define HEIGHT WIDTH
#define VOXEL_SPACE_SIZE 32.0f


struct VoxelBuilder {

   void draw();
   void update();

   void add_voxel(Vector3 index);
   void remove_voxel(Vector3 index);

   explicit VoxelBuilder(float size);

   VoxelPicker picker;
   Camera camera;
   Voxels voxels;
};


void VoxelBuilder::add_voxel(Vector3 index)
{
   // TODO: pallete color and sruff
   voxels[index] = 1;
}


void VoxelBuilder::remove_voxel(Vector3 index)
{
   voxels[index] = 0;
}


void VoxelBuilder::update()
{
   update_camera(&camera);
   bool left = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
   bool right = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);

   if ( !(left || right) ) return;
   picker.update(&voxels, camera);
   
   if ( !picker.selected ) return;

   if ( right ) remove_voxel(picker.remove_position); 
   if ( left ) add_voxel(picker.add_position);
}


void VoxelBuilder::draw()
{
   BeginMode3D(camera);

      draw_grid(camera.position, voxels.data.size());
      voxels.draw();

   EndMode3D();
}


VoxelBuilder::VoxelBuilder(float size)
   : voxels(size)
{
   init_camera(&camera, { size, size, size });
}


void draw_cube_at(Vector3 p, Color col)
{
   p = { p.x + 0.5f, p.y + 0.5f, p.z+0.5f };
   DrawCubeWiresV(p, {1, 1, 1}, col);
}


int main()
{
   InitWindow(WIDTH, HEIGHT, "voxel-builder");
   VoxelBuilder app(VOXEL_SPACE_SIZE);
   SetTargetFPS(60);

   while ( !WindowShouldClose() ) {
   
      app.update();
      
      BeginDrawing();
      ClearBackground(RAYWHITE);

      app.draw();
      //DrawText(TextFormat("pos: %0.2f, %0.2f %0.2f", pos.x, pos.y, pos.z), 10, 40, 20, BLACK);
      DrawFPS(10, 10);
      EndDrawing();
   }

   CloseWindow();
   
   return 0;
}
