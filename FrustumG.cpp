
/* ------------------------------------------------------

   View Frustum - Std3D

--------------------------------------------------------*/


#include "FrustumG.h"
#include <math.h>


FrustumG::FrustumG()
: mNearD(0.f), mFarD(0.f), mRatio(0.f), mFovY(0.f)
, mNW(0.f), mNH(0.f), mFW(0.f), mFH(0.f)
{}


void FrustumG::setCamInternals(float fovY, UInt32 width, UInt32 height, float nearD, float farD)
{
   mRatio = float(width)/float(height);
   mFovY = fovY;
   mNearD = nearD;
   mFarD = farD;

   float tang = (float)tan(ANG2RAD * mFovY * 0.5);

   mNH = mNearD * tang;
   mNW = mNH * mRatio;
   mFH = mFarD * tang;
   mFW = mFH * mRatio;
}


void FrustumG::update(const Vec3& eye, const Vec3& look, const Vec3& up)
{
   Vec3 z = eye - look;
   z.normalize();

   Vec3 x = Vec3::cross(z, up);
   x.normalize();

   Vec3 y = Vec3::cross(x, z);
   y.normalize();

////////////////////////////////////////////////////////////////

   const Vec3 nc = eye - z * mNearD;   // near clip, set by view-direction
   const Vec3 fc = eye - z * mFarD;    // far clip, set by view-direction

   mNTL = nc + y * mNH - x * mNW;
   mNTR = nc + y * mNH + x * mNW;
   mNBL = nc - y * mNH - x * mNW;
   mNBR = nc - y * mNH + x * mNW;

   mFTL = fc + y * mFH - x * mFW;
   mFTR = fc + y * mFH + x * mFW;
   mFBL = fc - y * mFH - x * mFW;
   mFBR = fc - y * mFH + x * mFW;

   mClipPlanes[P_TOP]    = Plane(mNTL, mFTL, mNTR);
   mClipPlanes[P_BOTTOM] = Plane(mNBR, mFBR, mNBL);
   mClipPlanes[P_LEFT]   = Plane(mNBL, mFBL, mNTL);
   mClipPlanes[P_RIGHT]  = Plane(mNTR, mFBR, mNBR);
   mClipPlanes[P_NEAR]   = Plane(mNTR, mNBR, mNTL);
   mClipPlanes[P_FAR]    = Plane(mFTL, mFBL, mFTR);
}


int FrustumG::pointInFrustum(const Vec3& p) const
{
   int result = INSIDE;
   for(int i = 0; i < P_AMOUNT; i++)
   {
      if (mClipPlanes[i].distance(p) < 0)
         return OUTSIDE;
   }
   return(result);
}


int FrustumG::sphereInFrustum(const Vec3& p, float radius) const
{
   int result = INSIDE;
   float distance;

   for(int i = 0; i < P_AMOUNT; i++)
   {
      distance = mClipPlanes[i].distance(p);
      if (distance < -radius)
         return OUTSIDE;
      else if (distance < radius)
         result =  INTERSECT;
   }
   return(result);
}


int FrustumG::boxInFrustum(const AABox& box) const
{
   int result = INSIDE;
   for(int i = 0; i < P_AMOUNT; i++)
   {
      if (mClipPlanes[i].distance(box.getVertexP(mClipPlanes[i].normal)) < 0)
         return OUTSIDE;
      else if (mClipPlanes[i].distance(box.getVertexN(mClipPlanes[i].normal)) < 0)
         result =  INTERSECT;
   }
   return(result);
}

