
/* ------------------------------------------------------

   View Frustum - Std3D

--------------------------------------------------------*/


#ifndef _FRUSTUM_
#define _FRUSTUM_

#include "Vec3.h"
#include "Matrix.hpp"
#include "Plane.h"
#include "AABox.h"


// Orbital position
struct CPosition
{
   CPosition::CPosition(const float pitch, const float yaw, const float radius)
      : mPitch(pitch)
      , mYaw(yaw)
      , mRadius(radius)
      , mLookAt()
   {
      this->update();
   }

   inline
   CPosition& operator += (float value)
   {
      mRadius = maximum(0.f, mRadius - value);
      return *this;
   }

   inline
   CPosition& operator -= (float value)
   {
      mRadius = maximum(0.f, mRadius + value);
      return *this;
   }

   float mPitch;
   float mYaw;
   float mRadius;
   Vec3 mLookAt;
   Matrix4x4 mView;

   void update();

   inline
   const Matrix4x4 getView() const
   {
      return mView;
   }

   Vec3 right() const
   {
      return Vec3(mView[0], mView[4], mView[8]);
   }
   Vec3 up() const
   {
      return Vec3(mView[1], mView[5], mView[9]);
   }
   Vec3 dir() const
   {
      return Vec3(mView[2], mView[6], mView[10]);
   }
};


inline
void CPosition::update()
{
   // the same as current implementation:
   mView = Matrix4x4::makeLookAt(mRadius, mPitch, mYaw, mLookAt);

   // the same current implementation:
   //return Matrix4x4::makeLookAt(mRadius, mPitch, mYaw, Vec3());

   ////////////////////////////////////////////////////////////////////////////////

   /* no-optimized implementation version:
   const Vec3 pos = makeSpherical(mPitch, mYaw, mRadius);
   return Matrix4x4::makeLookAt(pos, Vec3(), Vec3(0.f, 1.f, 0.f));
   */
}


class FrustumG
{
public:

   enum EClipPlane
   {
      P_TOP = 0,
      P_BOTTOM,
      P_LEFT,
      P_RIGHT,
      P_NEAR,
      P_FAR,
      P_AMOUNT
   };

   enum 
   { 
      OUTSIDE,  
      INSIDE, 
      INTERSECT 
   };

   FrustumG();

   void setCamInternals(float fovY, UInt32 width, UInt32 height, float nearD, float farD);

   void update(const Vec3& eye, const Vec3& lookAt, const Vec3& up);

   void print() const;

////////////////////////////////////////////////////////////////

   bool pointInFrustum(const Vec3& point) const;
   int sphereInFrustum(const Vec3& center, float radius) const;
   int boxInFrustum   (const AABox& box) const;

//protected:

   // clipping planes
   Plane mClipPlanes[P_AMOUNT];

   // frustum pyramid points
   Vec3 mNTL, mNTR, mNBL, mNBR, mFTL, mFTR, mFBL, mFBR;

   // camera configuration
   float mNearD, mFarD, mRatio, mFovY;

   // create for optimization, to avoid extra-calculation
   float mNW, mNH, mFW, mFH;

};


#endif
