
/* ------------------------------------------------------

   View - Std3D

--------------------------------------------------------*/

#ifndef _VIEW_
#define _VIEW_

#include "Matrix.hpp"

class CView
{
public:

   CView(const float pitch, const float yaw, const float radius)
      : mPitch(pitch)
      , mYaw(yaw)
      , mRadius(radius)
      , camPitch(0.f)
      , camYaw(0.f)
      , worldYaw(0.f)
      , movement(radius)
   {
   }


   Matrix4x4 calculateViewCameraRelated(const Vec3& eye, const Vec3& lookAt, const Vec3& up) const
   {
      Matrix4x4 viewMtx          = Matrix4x4::makeLookAt(eye, lookAt, up);                            // final view matrix.
      Matrix4x4 rotateRefCam     = Matrix4x4::makeRotateX(camPitch) * Matrix4x4::makeRotateY(camYaw); // camera coordinate-system rotation.
      Matrix4x4 rotateRefWorld   = Matrix4x4::makeRotateY(worldYaw);                                  // world coordinate-system rotation.

      // Make final view Matrix with movement but without any rotations.
      //viewMtx = Matrix4x4::makeTranslate(Vec3(0.f, 0.f, movement)) * viewMtx;

      // Apply rotation pitch+yaw around camera-origin in camera-coordinate system.
      viewMtx = rotateRefCam * viewMtx;

      // Apply rotation in world coordinate-system.
      viewMtx = viewMtx * rotateRefWorld;

      return viewMtx;
   }


   Matrix4x4 calculateViewOriginRelated(const Vec3& eye, const Vec3& lookAt, const Vec3& up) const
   {
      Matrix4x4 viewMtx          = Matrix4x4::makeLookAt(eye, lookAt, up); // final view matrix.
      Matrix4x4 rotateRefCam     = Matrix4x4::makeRotateX(camPitch);       // camera coordinate-system rotation.
      Matrix4x4 rotateRefWorld   = Matrix4x4::makeRotateY(worldYaw);       // world coordinate-system rotation.

      // Make final Matrix with movement but without any rotations.
      //viewMtx = Matrix4x4::makeTranslate(Vec3(0.f, 0.f, movement)) * viewMtx;

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


   Matrix4x4 calculateView() const
   {
      const Matrix4x4 worldRadiusRotation = Matrix4x4::makeRotateX(mPitch) * Matrix4x4::makeRotateY(mYaw);   // no matter the order of rotations.

      const Vec3 eye =  worldRadiusRotation * Vec3(0.f, 0.f, -movement);
      const Vec3 up  =  worldRadiusRotation * Vec3(0.f, 1.f,  0.f);
      const Vec3 lookAt(0.f, 0.f, 0.f);   // always look into origin(0,0,0).

      if (true)   // rotation related origin.
      {
         return calculateViewOriginRelated(eye, lookAt, up);
      }
      else        // rotation related camera.
      {
         return calculateViewCameraRelated(eye, lookAt, up);
      }
   }


//////////////////////////////////////////////////////////////////////////

   float mPitch;
   float mYaw;
   float mRadius;

public:

   float camPitch;
   float camYaw;
   float worldYaw;
   float movement;

};

#endif
