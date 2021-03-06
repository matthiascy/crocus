#include "Annulus.h"

const double Annulus::kEpsilon = 0.001;

Annulus::Annulus()
:GeometryObject(),center(),inner_radius(1.),outer_radius(2.),normal(0,1,0)
{}

Annulus::Annulus(const Point3D &c, const Normal &n, const double r_in,const double r_out)
:GeometryObject(),center(c),inner_radius(r_in),outer_radius(r_out),normal(n)
{}

Annulus::~Annulus()
{}

bool Annulus::hit(const Ray& ray, double& tmin, ShadeRec& sr)const
{
	float t = (center - ray.o ) * normal / (ray.d * normal);

	if( t <= kEpsilon)
		return false;

	Point3D p = ray.o + t * ray.d;

	if(center.distance(p) < outer_radius && center.distance(p)  > inner_radius)
	{
		tmin = t;
		sr.normal = normal;
		sr.local_hit_point = ray.o + t * ray.d;
		return true;
	}

	else
		return false;
}

bool Annulus::shadow_hit(const Ray& ray,float& tmin)const
{
	float t = (center - ray.o ) * normal / (ray.d * normal);

	if( t <= kEpsilon)
		return false;

	Point3D p = ray.o + t * ray.d;

	if( center.distance(p) < outer_radius && center.distance(p)  > inner_radius )
	{
		tmin = t;
		return true;
	}

	else
		return false;
}