
/* ------------------------------------------------------

   View - Std3D

--------------------------------------------------------*/

#include "View.hpp"


CView::CView(const float pitch, const float yaw, const float radius)
   : mPitch(pitch)
   , mYaw(yaw)
   , mRadius((float)::fabs(radius))
   , mLookAt()
   , mView()
{
   this->update();
}


void CView::update()
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

