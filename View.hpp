
/* ------------------------------------------------------

   View - Std3D

--------------------------------------------------------*/

#ifndef _VIEW_
#define _VIEW_

#include "Matrix.hpp"

// Orbital position
struct CView
{
   CView(const float pitch, const float yaw, const float radius);

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


   float mPitch;
   float mYaw;
   float mRadius;
   Vec3 mLookAt;
   Matrix4x4 mView;
};


#endif
