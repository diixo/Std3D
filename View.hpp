
/* ------------------------------------------------------

   View - Std3D

--------------------------------------------------------*/

#ifndef _VIEW_
#define _VIEW_

#include "Matrix.hpp"

class CView
{
public:

   CView(const float pitch, const float yaw, const float radius);


   Matrix4x4 calculateViewCameraRelated(const Vec3& eye, const Vec3& lookAt, const Vec3& up) const;


   Matrix4x4 calculateViewOriginRelated(const Vec3& eye, const Vec3& lookAt, const Vec3& up) const;


   Matrix4x4 calculateView() const;

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
