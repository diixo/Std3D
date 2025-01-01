
/* ------------------------------------------------------

   Plane - Std3D

--------------------------------------------------------*/


#ifndef _PLANE_
#define _PLANE_

#include "Vec3.h"

class Plane  
{
public:

	Vec3 normal;
	float d;

	Plane();
	Plane(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3);

	void set3Points(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3);
	void setNormalAndPoint(const Vec3 &normal, const Vec3 &point);
	void setCoefficients(float a, float b, float c, float d);
	float distance(const Vec3 &p) const;

	void print();

};


#endif
