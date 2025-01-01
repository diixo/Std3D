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
// c23 = a21 * b13 + a22 * b23 + a23 * b33 + a24 * b44
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

