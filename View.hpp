
/* ------------------------------------------------------

   View - Std3D

--------------------------------------------------------*/

#ifndef _VIEW_
#define _VIEW_

#include "Matrix.hpp"

// Orbital view
struct CView
{
   CView(const float pitch, const float yaw, const float radius, const Vec3& lookAt);

   void update();

   CView& operator += (float value)
   {
      mRadius = maximum(0.f, mRadius - value);
      return *this;
   }

   CView& operator -= (float value)
   {
      mRadius = maximum(0.f, mRadius + value);
      return *this;
   }

   const Matrix4x4& getView() const
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

   const Vec3& lookAt() const
   {
      return mLookAt;
   }

   Vec3 scroll_dir() const
   {
      Matrix3x3 Myaw = Matrix3x3::makeRotateY(this->mYaw);
      Myaw.transpose();
      return Vec3(Myaw.m[2], Myaw.m[5], Myaw.m[8]);
   }

   Vec3 scroll_right() const
   {
      Matrix3x3 Myaw = Matrix3x3::makeRotateY(this->mYaw);
      Myaw.transpose();
      return Vec3(Myaw.m[0], Myaw.m[3], Myaw.m[6]);
   }

   float mPitch;
   float mYaw;
   float mRadius;
   Vec3 mLookAt;
   Matrix4x4 mView;
};


#endif
