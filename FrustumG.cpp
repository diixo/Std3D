
/* ------------------------------------------------------

   View Frustum - Std3D

--------------------------------------------------------*/


#include "FrustumG.h"
#include <math.h>

FrustumG::FrustumG()
: vRight(1, 0, 0)
, vUp(0, 1, 0)
, vMovement(0, 0, 0)
{}


void FrustumG::setCamInternals(float fov_angle, UInt32 width, UInt32 height, float nearD, float farD) 
{
   mRatio = float(width)/float(height);
   mAngle = fov_angle;
   mNearD = nearD;
   mFarD = farD;
}


void FrustumG::setPosition(const Vec3& eye, const Vec3& look, const Vec3& up) 
{
   vDir = look - eye;
   vDir.normalize();

   vRight = Vec3::cross(up, vDir);

   vRight.normalize();

   vUp = Vec3::cross(vDir, vRight);
   vUp.normalize();

   vMovement = eye; //necessary

   update();
}


void FrustumG::update()
{
   float NW, NH, FW, FH;
   float tang = (float)tan(ANG2RAD * mAngle * 0.5);

   NH = mNearD * tang;
   NW = NH * mRatio; 
   FH = mFarD  * tang;
   FW = FH * mRatio;
////////////////////////////////////////////////////////////////

   Vec3 nc = vMovement + vDir * mNearD; // near clip, set by view-direction
   Vec3 fc = vMovement + vDir * mFarD;  // far clip, set by view-direction

   mNTL = nc + vUp * NH - vRight * NW;
   mNTR = nc + vUp * NH + vRight * NW;
   mNBL = nc - vUp * NH - vRight * NW;
   mNBR = nc - vUp * NH + vRight * NW;

   mFTL = fc + vUp * FH - vRight * FW;
   mFTR = fc + vUp * FH + vRight * FW;
   mFBL = fc - vUp * FH - vRight * FW;
   mFBR = fc - vUp * FH + vRight * FW;

   mClipPlanes[P_TOP]      = Plane(mFTL, mNTL, mNTR);
   mClipPlanes[P_BOTTOM]   = Plane(mFBR, mNBR, mNBL);
   mClipPlanes[P_LEFT]     = Plane(mFBL, mNBL, mNTL);
   mClipPlanes[P_RIGHT]    = Plane(mFBR, mNTR, mNBR);
   mClipPlanes[P_NEAR]     = Plane(mNBR, mNTR, mNTL);
   mClipPlanes[P_FAR]      = Plane(mFBL, mFTL, mFTR);

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

