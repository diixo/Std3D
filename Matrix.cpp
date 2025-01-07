/* ------------------------------------------------------

   Matrix - Std3D

--------------------------------------------------------*/


/** Mathematical representation:
*   [ m00 m01 m02 ] [x]  [ m00*x + m01*y + m02*z ]
*   [ m10 m11 m12 ]*[y] =[ m10*x + m11*y + m12*z ]
*   [ m20 m21 m22 ] [z]  [ m20*x + m21*y + m22*z ]
*/

/** OpenGL representation m[9]
*	[ m0 m3 m6 ]   [ m00 m01 m02 ]
*	[ m1 m4 m7 ] = [ m10 m11 m12 ]
*	[ m2 m5 m8 ]   [ m20 m21 m22 ]
*/

//////////////////////////////////////////////////////////////////////////

/** OpenGL representation m[16] **/

// [ a11 a12 a13 a14 ]   [ m0 m4 m8  m12 ]
// [ a21 a22 a23 a24 ] = [ m1 m5 m9  m13 ]
// [ a31 a32 a33 a34 ]   [ m2 m6 m10 m14 ]
// [ a41 a42 a43 a44 ]   [ m3 m7 m11 m15 ]

// [ a11 a12 a13 a14 ]   [ b11 b12 b13 b14 ]   [ c11 c12 c13 c14 ]
// [ a21 a22 a23 a24 ] x [ b21 b22 b23 b24 ] = [ c21 c22 c23 c24 ]
// [ a31 a32 a33 a34 ]   [ b31 b32 b33 b34 ]   [ c31 c32 c33 c34 ]
// [ a41 a42 a43 a44 ]   [ b41 b42 b43 b44 ]   [ c41 c42 c43 c44 ]

// c11 = a11 * b11 + a12 * b21 + a13 * b31 + a14 * b41
// c21 = a21 * b11 + a22 * b21 + a23 * b31 + a24 * b41
// c31 = a31 * b11 + a32 * b21 + a33 * b31 + a34 * b41
// c41 = a41 * b11 + a42 * b21 + a43 * b31 + a44 * b41

// c12 = a11 * b12 + a12 * b22 + a13 * b32 + a14 * b42
// c22 = a21 * b12 + a22 * b22 + a23 * b32 + a24 * b42
// c32 = a31 * b12 + a32 * b22 + a33 * b32 + a34 * b42
// c42 = a41 * b12 + a42 * b22 + a43 * b32 + a44 * b42

// c13 = a11 * b13 + a12 * b23 + a13 * b33 + a14 * b43
// c23 = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b43
// c33 = a31 * b13 + a32 * b23 + a33 * b33 + a34 * b43
// c43 = a41 * b13 + a42 * b23 + a43 * b33 + a44 * b43

// c14 = a11 * b14 + a12 * b24 + a13 * b34 + a14 * b44
// c24 = a21 * b14 + a22 * b24 + a23 * b34 + a24 * b44
// c34 = a31 * b14 + a32 * b24 + a33 * b34 + a34 * b44
// c44 = a41 * b14 + a42 * b24 + a43 * b34 + a44 * b44

#include "Matrix.hpp"

void mul3x3(const float* const a, const float* const b, float* const c)
{
   c[0]  = a[0]*b[0]  + a[3]*b[1]  + a[6] *b[2];
   c[1]  = a[1]*b[0]  + a[4]*b[1]  + a[7] *b[2];
   c[2]  = a[2]*b[0]  + a[5]*b[1]  + a[8] *b[2];

   c[3]  = a[0]*b[3]  + a[3]*b[4]  + a[6] *b[5];
   c[4]  = a[1]*b[3]  + a[4]*b[4]  + a[7] *b[5];
   c[5]  = a[2]*b[3]  + a[5]*b[4]  + a[8] *b[5];

   c[6]  = a[0]*b[6]  + a[3]*b[7]  + a[6] *b[8];
   c[7]  = a[1]*b[6]  + a[4]*b[7]  + a[7] *b[8];
   c[8]  = a[2]*b[6]  + a[5]*b[7]  + a[8] *b[8]; 
}

void mul4x4(const float* const a, const float* const b, float* const c)
{
   c[0]  = a[0]*b[0]  + a[4]*b[1]  + a[8] *b[2]  + a[12]*b[3];
   c[1]  = a[1]*b[0]  + a[5]*b[1]  + a[9] *b[2]  + a[13]*b[3];
   c[2]  = a[2]*b[0]  + a[6]*b[1]  + a[10]*b[2]  + a[14]*b[3];
   c[3]  = a[3]*b[0]  + a[7]*b[1]  + a[11]*b[2]  + a[15]*b[3];
   c[4]  = a[0]*b[4]  + a[4]*b[5]  + a[8] *b[6]  + a[12]*b[7];
   c[5]  = a[1]*b[4]  + a[5]*b[5]  + a[9] *b[6]  + a[13]*b[7];
   c[6]  = a[2]*b[4]  + a[6]*b[5]  + a[10]*b[6]  + a[14]*b[7];
   c[7]  = a[3]*b[4]  + a[7]*b[5]  + a[11]*b[6]  + a[15]*b[7];
   c[8]  = a[0]*b[8]  + a[4]*b[9]  + a[8] *b[10] + a[12]*b[11];
   c[9]  = a[1]*b[8]  + a[5]*b[9]  + a[9] *b[10] + a[13]*b[11];
   c[10] = a[2]*b[8]  + a[6]*b[9]  + a[10]*b[10] + a[14]*b[11];
   c[11] = a[3]*b[8]  + a[7]*b[9]  + a[11]*b[10] + a[15]*b[11];
   c[12] = a[0]*b[12] + a[4]*b[13] + a[8] *b[14] + a[12]*b[15];
   c[13] = a[1]*b[12] + a[5]*b[13] + a[9] *b[14] + a[13]*b[15];
   c[14] = a[2]*b[12] + a[6]*b[13] + a[10]*b[14] + a[14]*b[15];
   c[15] = a[3]*b[12] + a[7]*b[13] + a[11]*b[14] + a[15]*b[15];
}

Matrix4x4::Matrix4x4()
{
   identity();
}

void Matrix4x4::identity()
{
   for (register int i=0; i < 15; i++)
   {
      m[i]=0.f;
   }
   m[0]=m[5]=m[10]=m[15]=1.f;
}


Matrix4x4 Matrix4x4::operator*(const Matrix4x4& mtx) const
{
   Matrix4x4 c;
   mul4x4(m, mtx.m, c.m);
   return c;
}

Matrix4x4::operator float*()
{
   return static_cast<float*>(&m[0]);   
}


Matrix4x4::operator const float*() const 
{
   return static_cast<const float*>(&m[0]);
}


Matrix4x4 Matrix4x4::makeWorldToLocal(const Vec3& xAxis, const Vec3& yAxis, const Vec3& zAxis, const Vec3& origin)
{
   Matrix4x4 view;

   view.m[0] = xAxis.x;
   view.m[4] = xAxis.y;
   view.m[8] = xAxis.z;
   view.m[12] = -Vec3::dot(xAxis, origin);

   view.m[1] = yAxis.x;
   view.m[5] = yAxis.y;
   view.m[9] = yAxis.z;
   view.m[13] = -Vec3::dot(yAxis, origin);

   view.m[2] = zAxis.x;
   view.m[6] = zAxis.y;
   view.m[10] = zAxis.z;
   view.m[14] = -Vec3::dot(zAxis, origin);

   return view;
}


Matrix4x4 Matrix4x4::makeLookAt(const Vec3& eye, const Vec3& lookAt, const Vec3& up)
{
   Vec3 zAxis = eye - lookAt;
   zAxis.normalize();

   Vec3 xAxis = Vec3::cross(up, zAxis);
   xAxis.normalize();

   Vec3 yAxis = Vec3::cross(zAxis, xAxis);
   yAxis.normalize();

   return Matrix4x4::makeWorldToLocal(xAxis, yAxis, zAxis, eye);
}


Matrix4x4 Matrix4x4::makeLookAt(const float radius, const float pitch, const float yaw)
{
   /* The same implementation:

   Matrix4x4 Myaw = Matrix4x4::makeRotateY(mYaw);
   Myaw.transpose();

   return Matrix4x4::makeTranslate(Vec3(0.f, 0.f, -mRadius)) * Matrix4x4::makeRotateX(mPitch) * Myaw;

   M = M1 * M2 * M3 = M1 * (M2 * M3)
   */
   const double p = pitch * ANG2RAD;
   const double y = yaw * ANG2RAD;

   const double sn_p = sin(p);
   const double cs_p = cos(p);

   const double sn_y = sin(y);
   const double cs_y = cos(y);

   Matrix4x4 mtx;

   mtx.m[0] = (float)cs_y;
   mtx.m[1] = (float)(-sn_p * sn_y);
   mtx.m[2] = (float)(cs_p * sn_y);
   mtx.m[3] = 0.f;

   mtx.m[4] = 0.f;
   mtx.m[5] = (float)cs_p;
   mtx.m[6] = (float)sn_p;
   mtx.m[7] = 0.f;

   mtx.m[8] = (float)-sn_y;
   mtx.m[9] = (float)(-sn_p * cs_y);
   mtx.m[10] = (float)(cs_p * cs_y);
   mtx.m[11] = 0.f;

   mtx.m[12] = 0.f;
   mtx.m[13] = 0.f;
   mtx.m[14] = -radius;
   mtx.m[15] = 1.f;

   return mtx;
}


Matrix4x4 Matrix4x4::makeLookAt(const float radius, const float pitch, const float yaw, const Vec3& center)
{
   return Matrix4x4::makeLookAt(radius, pitch, yaw) * Matrix4x4::makeTranslate(center);
}


void Matrix4x4::invert()
{
   const float a0 = m[0] * m[5] - m[1] * m[4];
   const float a1 = m[0] * m[6] - m[2] * m[4];
   const float a2 = m[0] * m[7] - m[3] * m[4];
   const float a3 = m[1] * m[6] - m[2] * m[5];
   const float a4 = m[1] * m[7] - m[3] * m[5];
   const float a5 = m[2] * m[7] - m[3] * m[6];
   const float b0 = m[8] * m[13] - m[9] * m[12];
   const float b1 = m[8] * m[14] - m[10] * m[12];
   const float b2 = m[8] * m[15] - m[11] * m[12];
   const float b3 = m[9] * m[14] - m[10] * m[13];
   const float b4 = m[9] * m[15] - m[11] * m[13];
   const float b5 = m[10] * m[15] - m[11] * m[14];

   const float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
   //if ( !isZero(det) )
   {
      Matrix4x4 inverse;
      inverse.m[0] = +m[5] * b5 - m[6] * b4 + m[7] * b3;
      inverse.m[4] = -m[4] * b5 + m[6] * b2 - m[7] * b1;
      inverse.m[8] = +m[4] * b4 - m[5] * b2 + m[7] * b0;
      inverse.m[12] = -m[4] * b3 + m[5] * b1 - m[6] * b0;
      inverse.m[1] = -m[1] * b5 + m[2] * b4 - m[3] * b3;
      inverse.m[5] = +m[0] * b5 - m[2] * b2 + m[3] * b1;
      inverse.m[9] = -m[0] * b4 + m[1] * b2 - m[3] * b0;
      inverse.m[13] = +m[0] * b3 - m[1] * b1 + m[2] * b0;
      inverse.m[2] = +m[13] * a5 - m[14] * a4 + m[15] * a3;
      inverse.m[6] = -m[12] * a5 + m[14] * a2 - m[15] * a1;
      inverse.m[10] = +m[12] * a4 - m[13] * a2 + m[15] * a0;
      inverse.m[14] = -m[12] * a3 + m[13] * a1 - m[14] * a0;
      inverse.m[3] = -m[9] * a5 + m[10] * a4 - m[11] * a3;
      inverse.m[7] = +m[8] * a5 - m[10] * a2 + m[11] * a1;
      inverse.m[11] = -m[8] * a4 + m[9] * a2 - m[11] * a0;
      inverse.m[15] = +m[8] * a3 - m[9] * a1 + m[10] * a0;

      const float invDet = static_cast<float>(1.f) / det;
      inverse.m[0] *= invDet;
      inverse.m[1] *= invDet;
      inverse.m[2] *= invDet;
      inverse.m[3] *= invDet;
      inverse.m[4] *= invDet;
      inverse.m[5] *= invDet;
      inverse.m[6] *= invDet;
      inverse.m[7] *= invDet;
      inverse.m[8] *= invDet;
      inverse.m[9] *= invDet;
      inverse.m[10] *= invDet;
      inverse.m[11] *= invDet;
      inverse.m[12] *= invDet;
      inverse.m[13] *= invDet;
      inverse.m[14] *= invDet;
      inverse.m[15] *= invDet;

      *this = inverse;
   }
}


Matrix4x4 Matrix4x4::makeRotateX(const float angle)
{
   const double rad = angle * ANG2RAD;
   const float cs = (float)cos(rad);
   const float sn = (float)sin(rad);
   Matrix4x4 mat;
   mat.m[0] = 1.0; mat.m[4] = 0.0; mat.m[8] = 0.0;  mat.m[12] = 0.0;
   mat.m[1] = 0.0; mat.m[5] = cs;  mat.m[9] = -sn;  mat.m[13] = 0.0;
   mat.m[2] = 0.0; mat.m[6] = sn;  mat.m[10] = cs;  mat.m[14] = 0.0;
   mat.m[3] = 0.0; mat.m[7] = 0.0; mat.m[11] = 0.0; mat.m[15] = 1.0;
   return mat;
}


Matrix4x4 Matrix4x4::makeRotateY(const float angle)
{
   const double rad = angle * ANG2RAD;
   const float cs = (float)cos(rad);
   const float sn = (float)sin(rad);
   Matrix4x4 mat;
   mat.m[0] = cs;   mat.m[4] = 0.0; mat.m[8] = sn;   mat.m[12] = 0.0;
   mat.m[1] = 0.0;  mat.m[5] = 1.0; mat.m[9] = 0.0;  mat.m[13] = 0.0;
   mat.m[2] = -sn;  mat.m[6] = 0.0; mat.m[10] = cs;  mat.m[14] = 0.0;
   mat.m[3] = 0.0;  mat.m[7] = 0.0; mat.m[11] = 0.0; mat.m[15] = 1.0;
   return mat;
}


Matrix4x4 Matrix4x4::makeRotateZ(const float angle)
{
   const double rad = angle * ANG2RAD;
   const float cs = (float)cos(rad);
   const float sn = (float)sin(rad);
   Matrix4x4 mat;
   mat.m[0] = cs;  mat.m[4] = -sn;  mat.m[8] = 0.0;  mat.m[12] = 0.0;
   mat.m[1] = sn;  mat.m[5] = cs;   mat.m[9] = 0.0;  mat.m[13] = 0.0;
   mat.m[2] = 0.0; mat.m[6] = 0.0;  mat.m[10] = 1.0; mat.m[14] = 0.0;
   mat.m[3] = 0.0; mat.m[7] = 0.0;  mat.m[11] = 0.0; mat.m[15] = 1.0;
   return mat;
}

