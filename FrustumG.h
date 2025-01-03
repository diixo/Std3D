
/* ------------------------------------------------------

   View Frustum - Std3D

--------------------------------------------------------*/


#ifndef _FRUSTUM_
#define _FRUSTUM_

#include "Vec3.h"
#include "Matrix.hpp"
#include "Plane.h"
#include "AABox.h"


struct CPosition
{
   CPosition::CPosition(const float pitch, const float yaw, const float radius)
      : camPitch(pitch)
      , worldYaw(yaw)
      , movement(radius)
   {
   }

   float camPitch;
   float worldYaw;
   float movement;

   Matrix4x4 calculateView() const;
};


inline
Matrix4x4 CPosition::calculateView() const
{
   const Vec3 eye    (0.f, 0.f, -movement);
   const Vec3 up     (0.f, 1.f, 0.f);
   const Vec3 lookAt (0.f, 0.f, 0.f);  // always look into origin(0,0,0).

   Matrix4x4 viewMtx          = Matrix4x4::makeLookAt(eye, lookAt, up); // final view matrix.
   Matrix4x4 rotateRefCam     = Matrix4x4::makeRotateX(camPitch);       // camera coordinate-system rotation.
   Matrix4x4 rotateRefWorld   = Matrix4x4::makeRotateY(worldYaw);       // world coordinate-system rotation.

   // Calculate pitch around origin(0,0,0) in camera-coordinate system.
   {
      // Extract full translation-vector of camera-coordinate system.
      const Vec3 translation = Vec3(viewMtx.m[12], viewMtx[13], viewMtx[14]);

      // Make back movement camera-coordinate system to origin(0,0,0). 
      // Then make rotation (around camera axis coordinate-system) and then make movement to current position  again.
      rotateRefCam = Matrix4x4::makeTranslate(translation) * (rotateRefCam * Matrix4x4::makeTranslate(-translation));
   }

   // Apply rotation pitch around camera-origin in camera-coordinate system.
   viewMtx = rotateRefCam * viewMtx;

   // Apply rotation in world coordinate-system.
   viewMtx = viewMtx * rotateRefWorld;

   return viewMtx;
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

   Matrix4x4 calculateView() const;
};

inline
Matrix4x4 CMovement::calculateView() const
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

   Plane mClipPlanes[P_AMOUNT];                 ///< clipping planes

   Vec3 mNTL, mNTR, mNBL, mNBR, mFTL, mFTR, mFBL, mFBR;   ///< frustum pyramid points

   float mNearD, mFarD, mRatio, mFovY;            ///< camera configuration

   float mNW, mNH, mFW, mFH;

};


#endif
