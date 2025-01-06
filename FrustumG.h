
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
   {
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

   Matrix4x4 calculateLookAt() const;
   Matrix4x4 makeLookAt() const;
};


inline
Matrix4x4 CPosition::makeLookAt() const
{
   const Vec3 eye(0.f, 0.f, mRadius);

   Matrix4x4 rotateRefWorld = Matrix4x4::makeRotateY(mYaw);
   rotateRefWorld.transpose();

   return Matrix4x4::makeTranslate(-eye) * Matrix4x4::makeRotateX(mPitch) * rotateRefWorld;
}


inline
Matrix4x4 CPosition::calculateLookAt() const
{
   // the same as current implementation:
   return this->makeLookAt();

   // the same as current implementation:
   //return Matrix4x4::makeLookAt(mRadius, mPitch, mYaw, Vec3());

   ////////////////////////////////////////////////////////////////////////////////

   /* no-optimized implementation version:
   const Vec3 pos = makeSpherical(mPitch, mYaw, mRadius);
   return Matrix4x4::makeLookAt(pos, Vec3(), Vec3(0.f, 1.f, 0.f));
   */
}


struct CMovement
{
public:

   CMovement(const Vec3& vEye, const Vec3& vLookAt, const Vec3& vUp)
      : eye(vEye)
      , lookAt(vLookAt)
      , up(vUp)
      , pitch(0.f)
      , yaw(0.f)
      , forward(0.f)
      , side(0.f)
   {
   }

   Vec3 eye;
   Vec3 lookAt;
   Vec3 up;

   float pitch;
   float yaw;

   float forward; // movement ahead
   float side;    // movement aside

   Matrix4x4 calculateLookAt() const;
};

inline
Matrix4x4 CMovement::calculateLookAt() const
{
   Matrix4x4 viewMtx      = Matrix4x4::makeLookAt(eye, lookAt, up);                      // final view matrix.
   Matrix4x4 rotateRefCam = Matrix4x4::makeRotateX(pitch) * Matrix4x4::makeRotateY(yaw); // camera coordinate-system rotation.

   // Make final view Matrix with movement but without any rotations.
   viewMtx = Matrix4x4::makeTranslate(Vec3(side, 0.f, forward)) * viewMtx;

   // Apply rotation pitch around camera-origin in camera-coordinate system.
   viewMtx = rotateRefCam * viewMtx;

   return viewMtx;
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

   Plane mClipPlanes[P_AMOUNT];                    ///< clipping planes

   Vec3 mNTL, mNTR, mNBL, mNBR, mFTL, mFTR, mFBL, mFBR;   ///< frustum pyramid points

   float mNearD, mFarD, mRatio, mFovY;             ///< camera configuration

   // create for optimization, to avoid extra-calculation
   float mNW, mNH, mFW, mFH;

};


#endif
