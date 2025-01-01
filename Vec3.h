
/* ------------------------------------------------------

   Vec3 - Std3D

--------------------------------------------------------*/


#ifndef _VEC3_
#define _VEC3_

typedef unsigned int UInt32;
typedef int Int32;
typedef unsigned char UInt8;
typedef char Int8;

//#define ANG2RAD (3.14159265358979323846 / 180.0)
#define ANG2RAD (3.1415926f / 180.0f)

class Vec3  
{
public:

   enum {eX, eY, eZ};

   union 
   {
      float coord[3];
      struct
      {
         float x;
         float y;
         float z;
      };
   };


   Vec3(float x, float y, float z);
   Vec3();

   Vec3 operator +(const Vec3 &v) const;
   Vec3 operator -(const Vec3 &v) const;

   // crossProduct
   static Vec3 cross(const Vec3 &v0, const Vec3 &v1);
   Vec3 operator *(float t) const;
   Vec3 operator /(float t) const;
   Vec3 operator -(void)    const;

   float length() const;
   void  normalize();
   static float dot(const Vec3& v0, const Vec3  &v1);
   void  set(float x,float y, float z);

   float square() const;

   Vec3& abs();

   Vec3 getMin(const Vec3& v) const;

   void  print();

   bool operator == (const Vec3& rv) const;

};


/**
* Calculate minimum.
*/
// note: don't name it as min(), it will surely conflict.
template<typename T>
inline T minimum(const T left, const T right)
{
   return (left < right) ? left : right;
}

inline
Vec3 projectPointOnRay(const Vec3& origin, const Vec3& dir, const Vec3& pos)
{
   const float vsq   = Vec3::dot(dir, dir);
   const float proj  = Vec3::dot((pos - origin), dir);
   return (origin + dir*(proj / vsq));
}

#endif
