
/* ------------------------------------------------------

   Plane - Std3D

--------------------------------------------------------*/


#include "Plane.h"
#include <stdio.h>


Plane::Plane()
: d(0.f)
{}


Plane::Plane(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3)
{
	set3Points(v1,v2,v3);
}


void Plane::set3Points(const Vec3 &v1, const Vec3 &v2, const Vec3 &v3)
{
   //n = cross(b-a, c-a);
   //n.normalize();
   //d = -dot(n, a);

   normal = Vec3::cross((v3 - v2), (v1 - v2));

	normal.normalize();
   d = -Vec3::dot(normal, v2);
}

void Plane::setNormalAndPoint(const Vec3 &normal, const Vec3 &point)
{
	this->normal = normal;
	this->normal.normalize();
   d = -Vec3::dot(normal, point);
}

void Plane::setCoefficients(float a, float b, float c, float d)
{
	// set the normal vector
	normal.set(a,b,c);
	//compute the lenght of the vector
	float l = normal.length();
	// normalize the vector
	normal.set(a/l,b/l,c/l);
	// and divide d by th length as well
	this->d = d/l;
}


float Plane::distance(const Vec3 &p) const
{
   return (d + Vec3::dot(normal, p));
}

void Plane::print()
{
	printf("Plane(");normal.print();printf("# %f)",d);
}
