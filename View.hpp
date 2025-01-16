
/* ------------------------------------------------------

   View - Std3D

--------------------------------------------------------*/

#ifndef _VIEW_
#define _VIEW_

#include "Matrix.hpp"

// Orbital view
struct SPosition
{
   SPosition(const float pitch, const float yaw, const float radius, const Vec3& lookAt);

   void setRadius(float value)
   {
      mRadius = maximum(0.f, this->mRadius + value);
   }

   void setPitch(float value)
   {
      mPitch = normalize360(this->mPitch + value);
   }

   void setYaw(float value)
   {
      mYaw = normalize360(this->mYaw + value);
   }

   float mPitch;
   float mYaw;
   float mRadius;
   Vec3 mLookAt;

};

class CView
{
public:

   CView(const SPosition& position);

   const Matrix4x4& getMtxView() const
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

   Vec3 scroll_dir() const
   {
      Matrix3x3 Myaw = Matrix3x3::makeRotateY(mFinalPosition.mYaw);
      Myaw.transpose();
      return Vec3(Myaw.m[2], Myaw.m[5], Myaw.m[8]);
   }

   Vec3 scroll_right() const
   {
      Matrix3x3 Myaw = Matrix3x3::makeRotateY(mFinalPosition.mYaw);
      Myaw.transpose();
      return Vec3(Myaw.m[0], Myaw.m[3], Myaw.m[6]);
   }

   void update(const SPosition& position);

private:

   SPosition mFinalPosition;
   Matrix4x4 mView;
};


#endif
