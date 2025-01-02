
/* ------------------------------------------------------

   Matrix - Std3D

--------------------------------------------------------*/

#ifndef _MATRIX_
#define _MATRIX_

#include "Vec3.h"
#include <math.h>

class Matrix3x3
{
public:

   float m[9];

   Matrix3x3();

   Matrix3x3(
      const float r1c1, const float r2c1, const float r3c1,
      const float r1c2, const float r2c2, const float r3c2,
      const float r1c3, const float r2c3, const float r3c3
      );

   void identity();

   Vec3 operator * (const Vec3& v) const;
   Matrix3x3 operator * (const Matrix3x3& b) const;

   void transpose();
   void invert();

   float& operator[] (const Int32 idx);
   const float& operator[] (const Int32 idx) const;

   static Matrix3x3 makeRotateX( const float& angle );
   static Matrix3x3 makeRotateY( const float& angle );
   static Matrix3x3 makeRotateZ( const float& angle );

   static Matrix3x3 makeScale(const Vec3& sv);
};

inline 
Matrix3x3 Matrix3x3::makeScale(const Vec3& sv)
{
   Matrix3x3 mat;
   mat.m[0] = sv.x;
   mat.m[4] = sv.y;
   mat.m[8] = sv.z;
   return mat;
}

void mul3x3(const float* const a, const float* const b, float* const c);

inline 
float& Matrix3x3::operator[] (const Int32 idx)
{
   return m[idx];   
}


inline 
const float& Matrix3x3::operator[] (const Int32 idx) const
{
   return m[idx];   
}


inline void Matrix3x3::identity()
{
   m[0] = 1.f; m[3] = 0.f; m[6] = 0.f;
   m[1] = 0.f; m[4] = 1.f; m[7] = 0.f;
   m[2] = 0.f; m[5] = 0.f; m[8] = 1.f;
}


inline 
Vec3 Matrix3x3::operator * (const Vec3& v) const
{
   return Vec3( 
      m[0]*v.x + m[3]*v.y + m[6]*v.z,
      m[1]*v.x + m[4]*v.y + m[7]*v.z,
      m[2]*v.x + m[5]*v.y + m[8]*v.z);
}

inline 
void Matrix3x3::transpose()
{
   Matrix3x3 result;

   result[0] = m[0]; 
   result[3] = m[1]; 
   result[6] = m[2]; 

   result[1] = m[3]; 
   result[4] = m[4]; 
   result[7] = m[5]; 

   result[2] = m[6]; 
   result[5] = m[7]; 
   result[8] = m[8]; 

   *this = result;
}

inline 
void Matrix3x3::invert()
{
   transpose();
}


inline 
Matrix3x3::Matrix3x3(
   const float r1c1, const float r2c1, const float r3c1,
   const float r1c2, const float r2c2, const float r3c2,
   const float r1c3, const float r2c3, const float r3c3
   )
{
   m[0] = r1c1; m[3] = r1c2; m[6] = r1c3;
   m[1] = r2c1; m[4] = r2c2; m[7] = r2c3;
   m[2] = r3c1; m[5] = r3c2; m[8] = r3c3;
}

inline 
Matrix3x3::Matrix3x3()
{
   identity();
}



inline 
Matrix3x3 Matrix3x3::operator * (const Matrix3x3& b) const
{
   Matrix3x3 c;
   mul3x3(m, b.m, c.m);
   return c;
}


inline 
Matrix3x3 Matrix3x3::makeRotateX(const float& angle)
{
   const float rad = angle*ANG2RAD;
   const float Cos = (float)cos(rad);
   const float Sin = (float)sin(rad);
   Matrix3x3 mat;
   mat.m[0] = 1.f; mat.m[3] = 0.f; mat.m[6] = 0.f;
   mat.m[1] = 0.f; mat.m[4] = Cos; mat.m[7] = -Sin;
   mat.m[2] = 0.f; mat.m[5] = Sin; mat.m[8] = Cos;
   return mat;
}


inline 
Matrix3x3 Matrix3x3::makeRotateY(const float& angle)
{
   const float rad = angle*ANG2RAD;
   const float Cos = (float)cos(rad);
   const float Sin = (float)sin(rad);
   Matrix3x3 mat;
   mat.m[0] = Cos;  mat.m[3] = 0.f; mat.m[6] = Sin;
   mat.m[1] = 0.f;  mat.m[4] = 1.f; mat.m[7] = 0.f;
   mat.m[2] = -Sin; mat.m[5] = 0.f; mat.m[8] = Cos;
   return mat;
}


inline 
Matrix3x3 Matrix3x3::makeRotateZ(const float& angle)
{
   const float rad = angle*ANG2RAD;
   const float Cos = (float)cos(rad);
   const float Sin = (float)sin(rad);
   Matrix3x3 mat;
   mat.m[0] = Cos; mat.m[3] = -Sin; mat.m[6] = 0.f;
   mat.m[1] = Sin; mat.m[4] = Cos;  mat.m[7] = 0.f;
   mat.m[2] = 0.f; mat.m[5] = 0.f;  mat.m[8] = 1.f;
   return mat;
}


class Matrix4x4
{
public:

   float m[16];

   Matrix4x4();
   Matrix4x4 operator*(const Matrix4x4& mtx) const;

   // the operations of obtaining a reference to data
   operator			float*();
   operator const	float*() const;

   void identity();

   void transpose();
   void invert();

   explicit Matrix4x4(const Matrix3x3& rm);

   /// v' = M x v
   Vec3 operator * (const Vec3& v) const;


   static Matrix4x4 makeRotateX(const float angle);
   static Matrix4x4 makeRotateY(const float angle);
   static Matrix4x4 makeRotateZ(const float angle);
   static Matrix4x4 makeTranslate(const Vec3& v);
   static Matrix4x4 makeScale(const Vec3& sv);

   static Matrix4x4 makeWorldToLocal(const Vec3& xAxis, const Vec3& yAxis, const Vec3& zAxis, const Vec3& origin);
   static Matrix4x4 makeLookAt(const Vec3& eye, const Vec3& lookAt, const Vec3& up);

};

inline 
Matrix4x4 Matrix4x4::makeScale(const Vec3& sv)
{
   Matrix4x4 mat;
   mat.m[0 ] = sv.x;
   mat.m[5 ] = sv.y;
   mat.m[10] = sv.z;
   return mat;
}

inline 
Matrix4x4 Matrix4x4::makeWorldToLocal(const Vec3& xAxis, const Vec3& yAxis, const Vec3& zAxis, const Vec3& origin)
{
   Matrix4x4 view;

   view.m[0 ] = xAxis.x;
   view.m[4 ] = xAxis.y;
   view.m[8 ] = xAxis.z;
   view.m[12] = -Vec3::dot(xAxis, origin);

   view.m[1 ] = yAxis.x;
   view.m[5 ] = yAxis.y;
   view.m[9 ] = yAxis.z;
   view.m[13] = -Vec3::dot(yAxis, origin);

   view.m[2 ] = zAxis.x;
   view.m[6 ] = zAxis.y;
   view.m[10] = zAxis.z;
   view.m[14] = -Vec3::dot(zAxis, origin);

   return view;
}

inline
Matrix4x4 Matrix4x4::makeLookAt(const Vec3& eye, const Vec3& lookAt, const Vec3& up)
{
   Vec3 zAxis = lookAt - eye;
   zAxis.normalize();

   Vec3 xAxis = Vec3::cross(up, zAxis);
   xAxis.normalize();

   Vec3 yAxis = Vec3::cross(zAxis, xAxis);
   yAxis.normalize();

   return Matrix4x4::makeWorldToLocal(xAxis, yAxis, -zAxis, eye);
}

inline 
Matrix4x4::Matrix4x4(const Matrix3x3& rm)
{
   m[0] = rm[0];
   m[1] = rm[1];
   m[2] = rm[2];

   m[4] = rm[3];
   m[5] = rm[4];
   m[6] = rm[5];

   m[8]  = rm[6];
   m[9]  = rm[7];
   m[10] = rm[8];

   m[3] = m[7] = m[11] = m[12] = m[13] = m[14] = 0.f;
   m[15] = 1.f;
}

inline 
Vec3 Matrix4x4::operator * (const Vec3& v) const
{
   return Vec3( m[0]*v.x + m[4]*v.y + m[ 8]*v.z + m[12],
      m[1]*v.x + m[5]*v.y + m[ 9]*v.z + m[13],
      m[2]*v.x + m[6]*v.y + m[10]*v.z + m[14] );
}


inline 
void Matrix4x4::invert()
{
   const float a0 = m[ 0]*m[ 5] - m[ 1]*m[ 4];
   const float a1 = m[ 0]*m[ 6] - m[ 2]*m[ 4];
   const float a2 = m[ 0]*m[ 7] - m[ 3]*m[ 4];
   const float a3 = m[ 1]*m[ 6] - m[ 2]*m[ 5];
   const float a4 = m[ 1]*m[ 7] - m[ 3]*m[ 5];
   const float a5 = m[ 2]*m[ 7] - m[ 3]*m[ 6];
   const float b0 = m[ 8]*m[13] - m[ 9]*m[12];
   const float b1 = m[ 8]*m[14] - m[10]*m[12];
   const float b2 = m[ 8]*m[15] - m[11]*m[12];
   const float b3 = m[ 9]*m[14] - m[10]*m[13];
   const float b4 = m[ 9]*m[15] - m[11]*m[13];
   const float b5 = m[10]*m[15] - m[11]*m[14];

   const float det = a0*b5 - a1*b4 + a2*b3 + a3*b2 - a4*b1 + a5*b0;
   //if ( !isZero(det) )
   {
      Matrix4x4 inverse;
      inverse.m[ 0] = + m[ 5]*b5 - m[ 6]*b4 + m[ 7]*b3;
      inverse.m[ 4] = - m[ 4]*b5 + m[ 6]*b2 - m[ 7]*b1;
      inverse.m[ 8] = + m[ 4]*b4 - m[ 5]*b2 + m[ 7]*b0;
      inverse.m[12] = - m[ 4]*b3 + m[ 5]*b1 - m[ 6]*b0;
      inverse.m[ 1] = - m[ 1]*b5 + m[ 2]*b4 - m[ 3]*b3;
      inverse.m[ 5] = + m[ 0]*b5 - m[ 2]*b2 + m[ 3]*b1;
      inverse.m[ 9] = - m[ 0]*b4 + m[ 1]*b2 - m[ 3]*b0;
      inverse.m[13] = + m[ 0]*b3 - m[ 1]*b1 + m[ 2]*b0;
      inverse.m[ 2] = + m[13]*a5 - m[14]*a4 + m[15]*a3;
      inverse.m[ 6] = - m[12]*a5 + m[14]*a2 - m[15]*a1;
      inverse.m[10] = + m[12]*a4 - m[13]*a2 + m[15]*a0;
      inverse.m[14] = - m[12]*a3 + m[13]*a1 - m[14]*a0;
      inverse.m[ 3] = - m[ 9]*a5 + m[10]*a4 - m[11]*a3;
      inverse.m[ 7] = + m[ 8]*a5 - m[10]*a2 + m[11]*a1;
      inverse.m[11] = - m[ 8]*a4 + m[ 9]*a2 - m[11]*a0;
      inverse.m[15] = + m[ 8]*a3 - m[ 9]*a1 + m[10]*a0;

      const float invDet = static_cast<float>(1.f)/det;
      inverse.m[ 0] *= invDet;
      inverse.m[ 1] *= invDet;
      inverse.m[ 2] *= invDet;
      inverse.m[ 3] *= invDet;
      inverse.m[ 4] *= invDet;
      inverse.m[ 5] *= invDet;
      inverse.m[ 6] *= invDet;
      inverse.m[ 7] *= invDet;
      inverse.m[ 8] *= invDet;
      inverse.m[ 9] *= invDet;
      inverse.m[10] *= invDet;
      inverse.m[11] *= invDet;
      inverse.m[12] *= invDet;
      inverse.m[13] *= invDet;
      inverse.m[14] *= invDet;
      inverse.m[15] *= invDet;

      *this = inverse;
   }
}

inline
void Matrix4x4::transpose()
{
   Matrix4x4 result;

   result[0] = m[0];
   result[4] = m[1];
   result[8] = m[2];
   result[12] = m[3];

   result[1] = m[4];
   result[5] = m[5];
   result[9] = m[6];
   result[13] = m[7];

   result[2] = m[8];
   result[6] = m[9];
   result[10] = m[10];
   result[14] = m[11];

   result[3] = m[12];
   result[7] = m[13];
   result[11] = m[14];
   result[15] = m[15];

   *this = result;
}


inline 
Matrix4x4 Matrix4x4::makeTranslate(const Vec3& v)
{
   Matrix4x4 mat;
   mat.m[12] = v.x;
   mat.m[13] = v.y;
   mat.m[14] = v.z;
   return mat;
}


inline 
Matrix4x4 Matrix4x4::makeRotateX(const float angle)
{
   const float rad = angle*ANG2RAD;
   const float Cos = (float)cos(rad);
   const float Sin = (float)sin(rad);
   Matrix4x4 mat;
   mat.m[0] = 1.0; mat.m[4] = 0.0; mat.m[8] = 0.0;  mat.m[12] = 0.0;
   mat.m[1] = 0.0; mat.m[5] = Cos; mat.m[9] = -Sin; mat.m[13] = 0.0;
   mat.m[2] = 0.0; mat.m[6] = Sin; mat.m[10] = Cos; mat.m[14] = 0.0;
   mat.m[3] = 0.0; mat.m[7] = 0.0; mat.m[11] = 0.0; mat.m[15] = 1.0;
   return mat;
}



inline 
Matrix4x4 Matrix4x4::makeRotateY(const float angle)
{
   const float rad = angle*ANG2RAD;
   const float Cos = (float)cos(rad);
   const float Sin = (float)sin(rad);
   Matrix4x4 mat;
   mat.m[0] = Cos;  mat.m[4] = 0.0; mat.m[8] = Sin;  mat.m[12] = 0.0;
   mat.m[1] = 0.0;  mat.m[5] = 1.0; mat.m[9] = 0.0;  mat.m[13] = 0.0;
   mat.m[2] = -Sin; mat.m[6] = 0.0; mat.m[10] = Cos; mat.m[14] = 0.0;
   mat.m[3] = 0.0;  mat.m[7] = 0.0; mat.m[11] = 0.0; mat.m[15] = 1.0;
   return mat;
}



inline 
Matrix4x4 Matrix4x4::makeRotateZ(const float angle)
{
   const float rad = angle*ANG2RAD;
   const float Cos = (float)cos(rad);
   const float Sin = (float)sin(rad);
   Matrix4x4 mat;
   mat.m[0] = Cos; mat.m[4] = -Sin; mat.m[8] = 0.0;  mat.m[12] = 0.0;
   mat.m[1] = Sin; mat.m[5] = Cos;  mat.m[9] = 0.0;  mat.m[13] = 0.0;
   mat.m[2] = 0.0; mat.m[6] = 0.0;  mat.m[10] = 1.0; mat.m[14] = 0.0;
   mat.m[3] = 0.0; mat.m[7] = 0.0;  mat.m[11] = 0.0; mat.m[15] = 1.0;
   return mat;
}


void mul4x4(const float* const a, const float* const b, float* const c);


#endif
