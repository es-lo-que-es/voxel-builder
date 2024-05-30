#include "voxel_picker.hpp"
#include "stdio.h"
#include "raymath.h"


void VoxelPicker::exit_collision(float s)
{
   float d = 0.0000;
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
   float d = 0.0000;
   ray = GetMouseRay(GetMousePosition(), cam);
   
   printf("ray origin: %2.2f %2.2f %2.2f\n", ray.position.x, ray.position.y, ray.position.z);
   collision = GetRayCollisionBox(ray, {{0, 0, 0}, {s - d, s - d, s - d}});
   printf("collision: %2.2f %2.2f %2.2f\n", collision.point.x, collision.point.y, collision.point.z);
}


Vector3 no_zeroes(Vector3 v)
{
   float small = 0.000001;

   v.x = v.x == 0 ? v.x + small : v.x;
   v.y = v.y == 0 ? v.y + small : v.y;
   v.z = v.z == 0 ? v.z + small : v.z;

   return v;
}


Vector3 entry_edges(Vector3 entry, Vector3 exit, Vector3 dir)
{
   Vector3 diff;

   diff.x = (entry.x != exit.x && dir.x < 0) ? -1 : 0;
   diff.y = (entry.y != exit.y && dir.y < 0) ? -1 : 0;
   diff.z = (entry.z != exit.z && dir.z < 0) ? -1 : 0;

   return diff;
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


void VoxelPicker::DDA(Voxels * vox, Vector3 s, Vector3 e, Vector3 dir)
{
   trace.clear();

   int i = 0;
   dir = no_zeroes(dir);
   float steps[] = { 1, -1 };

   // current voxel
   Vector3 c = { _floor(s.x), _floor(s.y), _floor(s.z) };
   e = { _floor(e.x), _floor(e.y), _floor(e.z) };

   Vector3 step = { steps[dir.x < 0], steps[dir.y < 0], steps[dir.z < 0] };

   // next voxel boundary
   Vector3 nb = { c.x + step.x, c.y + step.y, c.z + step.z };
   printf("entry: %2.2f %2.2f %2.2f\n", c.x, c.y, c.z);

   // distance to the next voxel boundary
   Vector3 tmax = { (nb.x - s.x) / dir.x, (nb.y - s.y) / dir.y, (nb.z - s.z) / dir.z }; 
   Vector3 tdelta = { 1 / (dir.x * step.x), 1 / (dir.y * step.y), 1 / (dir.z * step.z) };
   
   // decrease indexes for negative directions
   c = Vector3Add(c, entry_edges(c, e, dir));

   printf("entry: %2.2f %2.2f %2.2f\n", c.x, c.y, c.z);
   printf("exit: %2.2f %2.2f %2.2f\n", e.x, e.y, e.z);

   while ( !Vector3Eq(c, e) ) {

      trace.push_back(c);
      printf("%2.2f %2.2f %2.2f\n", c.x, c.y, c.z);
      
      if ( c.x >= 0 and c.y >= 0 and c.z >= 0 ) {

         if ( (*vox)[c] != 0 ) {
            selected_pos = c;
            return;
         }
      } else {
         break;
      }

      if (tmax.x < tmax.y) {
         if (tmax.x < tmax.z) {
            c.x += step.x; tmax.x += tdelta.x;
         } else {
            c.z += step.z; tmax.z += tdelta.z;
         }
      } else {
         if (tmax.y < tmax.z) {
            c.y += step.y; tmax.y += tdelta.y;
         } else {
            c.z += step.z; tmax.z += tdelta.z;
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

   //selected_pos = { floorf(exit.x), floorf(exit.y), floorf(exit.z) };
   DDA(vox, entry, exit, dir);
}
