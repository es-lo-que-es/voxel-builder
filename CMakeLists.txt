cmake_minimum_required(VERSION 3.10)

project(voxel-builder)


add_executable(run src/main.cpp)
target_link_libraries(run raylib)
