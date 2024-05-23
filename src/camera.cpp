#include "camera.hpp"
#include <raylib.h>
#include "math.h"
#include "rcamera.h"


void update_camera(Camera * cam)
{
   Vector3 none = { 0, 0, 0 };

   float yaw = IsKeyDown(KEY_D) * 0.1 - IsKeyDown(KEY_A) * 0.1;
   float pitch = IsKeyDown(KEY_S) * 0.1 - IsKeyDown(KEY_W) * 0.1;

   Vector3 pos = cam->position;
   CameraPitch(cam, pitch, true, true, false);
   // i cant be bothered rewriting CameraPitch() vertical clamping
   cam->position = cam->position.y <= 0 ? pos : cam->position;

   CameraYaw(cam, yaw, true);

   float zoom = GetMouseWheelMove() * -0.92;
   CameraMoveToTarget(cam, zoom);
}
