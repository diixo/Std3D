
/* ------------------------------------------------------

   Axis Aligned Boxes - Std3D

--------------------------------------------------------*/


#ifndef _AABOX_
#define _AABOX_

#include "Vec3.h"


class AABox
{
public:
   enum EOrientation
   {
      OUTSIDE,
      INSIDE
   };

public:

   AABox();
   AABox(const Vec3& pos, float x, float y, float z);

   // for use in frustum computations
   Vec3 getVertexP(const Vec3 &normal) const;
   Vec3 getVertexN(const Vec3 &normal) const;

   /// construct new bounding volume from two points
   void set(const Vec3& p1, const Vec3& p2);
   void set(const Vec3& pos, float x, float y, float z);

   const Vec3& position() const;
   const Vec3& size() const;

   Vec3& position();
   Vec3& size();

   /// check if point places inside bounding volume
   EOrientation test(const Vec3& p) const;

   UInt8 is_in(const AABox& box, int dim0, int dim1) const;

private:

   ///< Bounding volume size (a half of real volume size)
   Vec3	  mSize;

   ///< Bounding volume position (center)
   Vec3    mPosition;
};

inline 
const Vec3& AABox::position() const
{
   return mPosition;
}

inline 
const Vec3& AABox::size() const
{
   return mSize;
}

inline 
Vec3& AABox::position()
{
   return mPosition;
}

inline 
Vec3& AABox::size()
{
   return mSize;
}


#endif
