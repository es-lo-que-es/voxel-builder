#include "camera.hpp"
#include "voxel.hpp"
#include "grid.hpp"
#include "voxel_picker.hpp"
#include "color_picker.hpp"

#define WIDTH 600.0f
#define COLOR_PICKER_SIZE 30.0f

#define HEIGHT WIDTH
#define VOXEL_SPACE_SIZE 32.0f


Color BACKGROUND = RAYWHITE;
Vector2 COLOR_PICKER_POS = { WIDTH - COLOR_PICKER_SIZE, 0 };


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


void VoxelBuilder::add_voxel(Vector3 index)
{
   voxels[index] = color_picker.selected_index;
}


void VoxelBuilder::remove_voxel(Vector3 index)
{
   voxels[index] = 0;
}


void VoxelBuilder::update()
{
   update_camera(&camera);
   
   color_picker.update();
   if ( color_picker.updated ) return;

   bool left = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
   bool right = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);

   if ( !(left || right) ) return;
   voxel_picker.update(&voxels, camera);
   
   if ( !voxel_picker.selected ) return;

   if ( right ) remove_voxel(voxel_picker.remove_position); 
   if ( left ) add_voxel(voxel_picker.add_position);
}


void VoxelBuilder::draw() const
{
   BeginDrawing();

      ClearBackground(BACKGROUND);

      BeginMode3D(camera);
         draw_grid(camera.position, voxels.data.size());
         voxels.draw(&color_picker.palette);
      EndMode3D();

      color_picker.draw();
      DrawFPS(10, 10);

   EndDrawing();
}


VoxelBuilder::VoxelBuilder(float size)
   : voxels(size),
     color_picker(COLOR_PICKER_POS, COLOR_PICKER_SIZE)
{
   init_camera(&camera, { size, size, size });
}


void VoxelBuilder::run()
{
   while ( !WindowShouldClose() ) {
      update();
      draw();
   }
}


int main()
{
   InitWindow(WIDTH, HEIGHT, "voxel-builder");
   SetTargetFPS(60);
   
   VoxelBuilder app(VOXEL_SPACE_SIZE);
   app.run();

   CloseWindow();
   
   return 0;
}
