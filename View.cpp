
/* ------------------------------------------------------

   View - Std3D

--------------------------------------------------------*/

#include "View.hpp"


SPosition::SPosition(const float pitch, const float yaw, const float radius, const Vec3& lookAt)
   : mPitch(pitch)
   , mYaw(yaw)
   , mRadius((float)::fabs(radius))
   , mLookAt(lookAt)
{
}

CView::CView(const SPosition& position)
   : mFinalPosition(0.f, 0.f, 0.f, Vec3())
   , mView()
{
   this->update(position);
}

void CView::update(const SPosition& position)
{
   mFinalPosition = position;

   // the same as current implementation:
   mView = Matrix4x4::makeLookAt(
      mFinalPosition.mRadius,
      mFinalPosition.mPitch,
      mFinalPosition.mYaw,
      mFinalPosition.mLookAt);

   // the same current implementation:
   //return Matrix4x4::makeLookAt(mRadius, mPitch, mYaw, Vec3());

   ////////////////////////////////////////////////////////////////////////////////

   /* no-optimized implementation version:
   const Vec3 pos = makeSpherical(mPitch, mYaw, mRadius);
   return Matrix4x4::makeLookAt(pos, Vec3(), Vec3(0.f, 1.f, 0.f));
   */
}

