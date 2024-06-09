#include "voxel_builder.hpp"
#include "config.hpp"
#include "camera.hpp"
#include "grid.hpp"


void draw_help()
{
   Color col = HELP_COLOR;

   Vector2 pos = HELP_POS;
   DrawText("LMB - draw;          RMB - erase", pos.x, pos.y, HELP_FONT_SIZE, col);

   pos.y += HELP_FONT_SIZE;
   DrawText("W,A,S,D - rotate;    ESC - clear all", pos.x, pos.y, HELP_FONT_SIZE, col);
}


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
   if ( IsKeyReleased(KEY_ESCAPE) ) voxels.clear();

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
      draw_help();

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
