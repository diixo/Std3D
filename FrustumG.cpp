
/* ------------------------------------------------------

   View Frustum - Std3D

--------------------------------------------------------*/


#include "FrustumG.h"
#include <math.h>


FrustumG::FrustumG()
: mNearD(0.f), mFarD(0.f), mRatio(0.f), mAngle(0.f)
, NW(0.f), NH(0.f), FW(0.f), FH(0.f)
{}


void FrustumG::setCamInternals(float fov_angle, UInt32 width, UInt32 height, float nearD, float farD) 
{
   mRatio = float(width)/float(height);
   mAngle = fov_angle;
   mNearD = nearD;
   mFarD = farD;

   float tang = (float)tan(ANG2RAD * mAngle * 0.5);

   NH = mNearD * tang;
   NW = NH * mRatio;
   FH = mFarD * tang;
   FW = FH * mRatio;
}


void FrustumG::update(const Vec3& eye, const Vec3& look, const Vec3& up)
{
   Vec3 vDir = look - eye;
   vDir.normalize();

   Vec3 vRight = Vec3::cross(up, vDir);
   vRight.normalize();

   Vec3 vUp = Vec3::cross(vDir, vRight);
   vUp.normalize();

////////////////////////////////////////////////////////////////

   Vec3 nc = eye + vDir * mNearD; // near clip, set by view-direction
   Vec3 fc = eye + vDir * mFarD;  // far clip, set by view-direction

   mNTL = nc + vUp * NH - vRight * NW;
   mNTR = nc + vUp * NH + vRight * NW;
   mNBL = nc - vUp * NH - vRight * NW;
   mNBR = nc - vUp * NH + vRight * NW;

   mFTL = fc + vUp * FH - vRight * FW;
   mFTR = fc + vUp * FH + vRight * FW;
   mFBL = fc - vUp * FH - vRight * FW;
   mFBR = fc - vUp * FH + vRight * FW;

   mClipPlanes[P_TOP]    = Plane(mFTL, mNTL, mNTR);
   mClipPlanes[P_BOTTOM] = Plane(mFBR, mNBR, mNBL);
   mClipPlanes[P_LEFT]   = Plane(mFBL, mNBL, mNTL);
   mClipPlanes[P_RIGHT]  = Plane(mFBR, mNTR, mNBR);
   mClipPlanes[P_NEAR]   = Plane(mNBR, mNTR, mNTL);
   mClipPlanes[P_FAR]    = Plane(mFBL, mFTL, mFTR);
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

