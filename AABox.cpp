
/* ------------------------------------------------------

   Axis Aligned Boxes - Std3D

--------------------------------------------------------*/


#include "AABox.h"

AABox::AABox()
{}

AABox::AABox(const Vec3& pos, float fx, float fy, float fz)
{
   set(pos, fx, fy, fz);
}

void AABox::set(const Vec3& pos, float x, float y, float z)
{
   mPosition = pos;

   if (x < 0.0) {
      mSize.x = -x;
      mPosition.x -= x;
   }
   if (y < 0.0) {
      mSize.y = -y;
      mPosition.y -= y;
   }
   if (z < 0.0) {
      mSize.z = -z;
      mPosition.z -= z;
   }
   mSize.x = x;
   mSize.y = y;
   mSize.z = z;
}


void AABox::set(const Vec3& p1, const Vec3& p2)
{
   // turn box inside-out: mins > maxs
   mPosition = p1.getMin(p2); 
   mSize = p1 - p2;
   mSize.abs();
}


AABox::EOrientation AABox::test(const Vec3& pos) const
{
   const Vec3 pMax = mPosition + mSize;

   //// check if the point is inside the volume
   if( pos.x >= mPosition.x && pos.x <= pMax.x &&
       pos.y >= mPosition.y && pos.y <= pMax.y &&
       pos.z >= mPosition.z && pos.z <= pMax.z )
   {
      return INSIDE;
   }

   return OUTSIDE;
}

UInt8 AABox::is_in(const AABox& box, int dim0, int dim1) const
{
   const Vec3 pMax = mPosition + mSize;

   const Vec3 boxMax = box.mPosition + box.mSize;

   UInt8 b0 = 0;
   UInt8 b1 = 0;
   UInt8 b2 = 0;
   UInt8 b3 = 0;

   //// check Position
   if( box.mPosition.coord[dim0] >= mPosition.coord[dim0] && box.mPosition.coord[dim0] <= pMax.coord[dim0] &&
       box.mPosition.coord[dim1] >= mPosition.coord[dim1] && box.mPosition.coord[dim1] <= pMax.coord[dim1]
      )
   {
      b0 = 1;
   }

   //// check Max
   if( boxMax.coord[dim0] >= mPosition.coord[dim0] && boxMax.coord[dim0] <= pMax.coord[dim0] &&
       boxMax.coord[dim1] >= mPosition.coord[dim1] && boxMax.coord[dim1] <= pMax.coord[dim1]
   )
   {
      b1 = 1;
   }


   if( box.mPosition.coord[dim0] >= mPosition.coord[dim0] && box.mPosition.coord[dim0] <= pMax.coord[dim0] &&
       boxMax.coord[dim1] >= mPosition.coord[dim1] && boxMax.coord[dim1] <= pMax.coord[dim1]
   )
   {
      b2 = 1;
   }


   if( boxMax.coord[dim0] >= mPosition.coord[dim0] && boxMax.coord[dim0] <= pMax.coord[dim0] &&
       box.mPosition.coord[dim1] >= mPosition.coord[dim1] && box.mPosition.coord[dim1] <= pMax.coord[dim1]
   )
   {
      b3 = 1;
   }


   return (b0 + b1 + b2 + b3);
}

Vec3 AABox::getVertexP(const Vec3 &normal) const
{
   Vec3 res = mPosition;

   if (normal.x > 0)
      res.x += mSize.x;

   if (normal.y > 0)
      res.y += mSize.y;

   if (normal.z > 0)
      res.z += mSize.z;

   return(res);
}



Vec3 AABox::getVertexN(const Vec3 &normal) const
{
   Vec3 res = mPosition;

   if (normal.x < 0.f)
      res.x += mSize.x;

   if (normal.y < 0.f)
      res.y += mSize.y;

   if (normal.z < 0.f)
      res.z += mSize.z;

   return(res);
}
