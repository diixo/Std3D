
/* ------------------------------------------------------

   Vec3 - Std3D

--------------------------------------------------------*/


#include "Vec3.h"

#include <math.h>
#include <stdio.h>


Vec3::Vec3()
: x(0.f)
, y(0.f)
, z(0.f)
{
}


Vec3::Vec3(float fx, float fy, float fz)
: x(fx)
, y(fy)
, z(fz)
{
}

//////////////////////////////////////////////////////////////////////
// Methods
//////////////////////////////////////////////////////////////////////

Vec3 Vec3::operator + (const Vec3 &v) const
{
	return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator - (const Vec3 &v) const
{
	return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3& Vec3::operator += (const Vec3& v)
{
   x += v.x;
   y += v.y;
   z += v.z;
   return *this;
}

Vec3& Vec3::operator -= (const Vec3& v)
{
   x -= v.x;
   y -= v.y;
   z -= v.z;
   return *this;
}

Vec3 Vec3::operator-() const
{
	return Vec3(-x, -y, -z);
}

// cross product
Vec3 Vec3::cross(const Vec3 &v0, const Vec3 &v1)
{
	return Vec3(
	   v0.y * v1.z - v0.z * v1.y,
	   v0.z * v1.x - v0.x * v1.z,
	   v0.x * v1.y - v0.y * v1.x
   );
}

Vec3 Vec3::operator*(float t) const
{
	return Vec3(x * t, y * t, z * t);
}

Vec3 Vec3::operator/(float t) const
{
	return Vec3(x / t, y / t, z / t);
}

float Vec3::length() const
{
	return((float)sqrt(x*x + y*y + z*z));
}

void Vec3::normalize()
{
	float len = length();
	if (len > 0.0)
   {
		x /= len;
		y /= len;
		z /= len;
	}
}

float Vec3::dot(const Vec3& v0, const Vec3  &v1)
{
	return (v0.x * v1.x + v0.y * v1.y + v0.z * v1.z);
}

void Vec3::set(float fx,float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}

float Vec3::square() const 
{
   return (x*x + y*y + z*z);
}


void Vec3::print(const char* name) const
{
	printf("%s Vec3(%f, %f, %f)\n", name, x, y, z);
}


Vec3& Vec3::abs()
{
   x = (float)::fabs(x);
   y = (float)::fabs(y);
   z = (float)::fabs(z);

   return *this;
}

Vec3 Vec3::getMin(const Vec3& v) const
{
   return Vec3(minimum(x, v.x), minimum(y, v.y), minimum(z, v.z));
}

bool Vec3::operator == (const Vec3& rv) const
{
   return ((x == rv.x) && (y == rv.y) && (z == rv.z));
}


Vec3 makeSpherical(const float rho, const float theta, const float radius)
{
   const double pitch = rho * ANG2RAD;
   const double yaw = theta * ANG2RAD;

   return Vec3(
      radius * (float)(cos(pitch) * sin(yaw)),
      radius * (float)sin(pitch),
      radius * (float)(cos(pitch) * cos(yaw))
   );
}
