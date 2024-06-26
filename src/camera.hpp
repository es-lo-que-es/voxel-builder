#ifndef CAMERA_HEADER_HPP
#define CAMERA_HEADER_HPP

#include <raylib.h>

extern float CAMERA_ANGLE;

void init_camera(Camera * cam, Vector3 pos);
void update_camera(Camera * cam);

#endif
