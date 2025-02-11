
/* ------------------------------------------------------

   Vec3 - Std3D

--------------------------------------------------------*/


#ifndef _VEC3_
#define _VEC3_

typedef unsigned int UInt32;
typedef int Int32;
typedef unsigned char UInt8;
typedef char Int8;

#define ANG2RAD (3.14159265358979323846 / 180.0)
//#define ANG2RAD (3.1415926f / 180.0f)

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

   Vec3& operator +=(const Vec3 &v);
   Vec3& operator -=(const Vec3 &v);

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

   void print(const char* name="") const;

   bool operator == (const Vec3& rv) const;

};


/**
* Calculate minimum.
*/
template<typename T>
inline T minimum(const T left, const T right)
{
   return (left < right) ? left : right;
}

template<typename T>
inline T maximum(const T left, const T right)
{
   return (left > right) ? left : right;
}

template <typename T>
inline T normalize360(const T angle)
{
   if (angle < 0.f)
      return (360.f + angle);
   if (angle > 360.f)
      return (angle - 360.f);
   return angle;
}


Vec3 makeSpherical(const float rho, const float theta, const float radius);


#endif
