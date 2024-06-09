cmake_minimum_required(VERSION 3.10)

project(voxel-builder)


set ( SRC
   src/voxel_builder.cpp
   src/color_picker.cpp
   src/voxel_picker.cpp

   src/palette.cpp
   src/camera.cpp

   src/voxel.cpp
   src/grid.cpp

   src/main.cpp
)


add_executable(voxel-builder ${SRC})
target_link_libraries(voxel-builder raylib m)
