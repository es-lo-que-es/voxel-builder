#include "voxel_picker.hpp"
#include "stdio.h"
#include "raymath.h"


void VoxelPicker::exit_collision(float s)
{
   float d = 0.0001;
   float distance = s * 2;
   Vector3 p = collision.point;
   
   // move ray start along direction by size * 2
   float x = p.x + distance * ray.direction.x;
   float y = p.y + distance * ray.direction.y;
   float z = p.z + distance * ray.direction.z;

   // cast ray in an opposite direction
   ray.direction = Vector3Negate(ray.direction);
   ray.position = { x, y, z };

   collision = GetRayCollisionBox(ray, {{0, 0, 0}, {s - d, s - d, s - d}});
}


void VoxelPicker::entry_collision(Camera cam, float s)
{
   float d = 0.0001;
   ray = GetMouseRay(GetMousePosition(), cam);
   
   printf("ray origin: %2.2f %2.2f %2.2f\n", ray.position.x, ray.position.y, ray.position.z);
   collision = GetRayCollisionBox(ray, {{0, 0, 0}, {s - d, s - d, s - d}});
   printf("collision: %f %f %f\n", collision.point.x, collision.point.y, collision.point.z);
}


Vector3 no_zeroes(Vector3 v)
{
   float small = 0.00001;

   v.x = v.x == 0 ? v.x + small : v.x;
   v.y = v.y == 0 ? v.y + small : v.y;
   v.z = v.z == 0 ? v.z + small : v.z;

   return v;
}


Vector3 next_boundary(Vector3 index, Vector3 dir)
{
   index.x = index.x + (dir.x > 0 ? 1 : 0);
   index.y = index.y + (dir.y > 0 ? 1 : 0);
   index.z = index.z + (dir.z > 0 ? 1 : 0);

   return index;
}


bool Vector3Eq(Vector3 a, Vector3 b)
{
   return a.x == b.x && a.y == b.y && a.z == b.z;
}


// floorf returns -1 when flooring -0.0
float _floor(float f)
{
   return (float)((int)f); 
}

Vector3 vector3_floor(Vector3 a)
{
   return { _floor(a.x), _floor(a.y), _floor(a.z) };
}


Vector3 get_tmax(Vector3 start, Vector3 next_bound, Vector3 dir)
{
   Vector3 tmax;

   tmax.x = (next_bound.x - start.x) / dir.x;
   tmax.y = (next_bound.y - start.y) / dir.y;
   tmax.z = (next_bound.z - start.z) / dir.z; 

   return tmax;
}


Vector3 get_tdelta(Vector3 dir)
{
   Vector3 tdelta;

   tdelta.x = 1 / abs(dir.x);
   tdelta.y = 1 / abs(dir.y);
   tdelta.z = 1 / abs(dir.z);

   return tdelta;
}

// WARNING: the edge values are dodged by colliding with a box a bit smaller 
// than actual voxel space, which will provide some degree of precision error
// for the extrmely large voxel space grid

void VoxelPicker::DDA(Voxels * vox, Vector3 s, Vector3 e, Vector3 dir)
{
   dir = no_zeroes(dir);
   float steps[] = { 1, -1 };

   e = vector3_floor(e);
   Vector3 index = vector3_floor(s);

   Vector3 nb = next_boundary(index, dir);
   Vector3 step = { steps[dir.x < 0], steps[dir.y < 0], steps[dir.z < 0] };

   // distance to the next voxel boundary
   Vector3 tdelta = get_tdelta(dir);
   Vector3 tmax = get_tmax(s, nb, dir);
   
   while ( !Vector3Eq(index, e) ) {

      if ( (*vox)[index] != 0 ) {
         selected_pos = index;
         return; 
      }

      if (tmax.x < tmax.y) {
         if (tmax.x < tmax.z) {
            index.x += step.x; tmax.x += tdelta.x;
         } else {
            index.z += step.z; tmax.z += tdelta.z;
         }
      } else {
         if (tmax.y < tmax.z) {
            index.y += step.y; tmax.y += tdelta.y;
         } else {
            index.z += step.z; tmax.z += tdelta.z;
         }
      }
   }

   selected_pos = e;
}


void VoxelPicker::update(Voxels * vox, Camera cam)
{
   float size = vox->data.size();
   entry_collision(cam, size);

   selected = collision.hit;
   if ( !selected ) return;

   // save entry collision data
   Vector3 entry = collision.point;
   Vector3 dir = ray.direction;

   exit_collision(size);
   Vector3 exit = collision.point;

   DDA(vox, entry, exit, dir);
}
