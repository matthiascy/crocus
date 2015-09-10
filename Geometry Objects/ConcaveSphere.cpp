#include "ConcaveSphere.h"
#include "Vector3D.h"
#include "Maths.h"
#include "Constants.h"


ConcaveSphere::ConcaveSphere()
:Sphere()
{}

ConcaveSphere::ConcaveSphere(const Point3D& p,const double r)
:Sphere(p,r)
{}

ConcaveSphere::~ConcaveSphere()
{}

bool ConcaveSphere::hit(const Ray& ray,double& tmin,ShadeRec &sr)const
{
	double t;
	Vector3D temp = ray.o - center;
	double a = ray.d * ray.d;
	double b = 2.0 * temp * ray.d;
	double c = temp * temp - radius * radius;
	double disc = b * b - 4.0 * a * c;

	if(disc < 0.0)
		return false;
	else
	{
		double e = sqrt(disc);
		double demon = 2.0 * a;
		t = ( -b - e ) / demon;

		if( t > kEpsilon )
		{
			tmin = t;
			sr.normal 	 = -1 * (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return true;
		}

		t = (-b + e) / demon;
		if( t > kEpsilon )
		{
			tmin = t;
			sr.normal   = -1 * (temp + t * ray.d) / radius;
			sr.local_hit_point = ray.o + t * ray.d;
			return true;
		}

	}
	return false;
}