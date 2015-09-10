#include "PartAnnulus.h"
#include "Constants.h"
#include "Material.h"
#include <math.h>

PartAnnulus::PartAnnulus(void):
GeometryObject(),
y(0.0),
inner_radius(0.8),
outer_radius(1.0),
phi_min(0.0),
phi_max(TWO_PI),
i_r_squared(0.64),
o_r_squared(1.0),
normal_up(true)
{}

PartAnnulus::PartAnnulus(const double y, double i_r, double o_r,
						 const double azimuth_min,	// in degrees
						 const double azimuth_max, // in degrees
						 bool up):
GeometryObject(),
y(y),
inner_radius(i_r),
outer_radius(o_r),
phi_min(azimuth_min * PI_ON_180),
phi_max(azimuth_max * PI_ON_180),
i_r_squared(inner_radius * inner_radius),
o_r_squared(outer_radius * outer_radius),
normal_up(up)
{}

PartAnnulus::PartAnnulus(const PartAnnulus& partAnnulus):
GeometryObject(partAnnulus),
y(partAnnulus.y),
inner_radius(partAnnulus.inner_radius),
outer_radius(partAnnulus.outer_radius),
phi_min(partAnnulus.phi_min),
phi_max(partAnnulus.phi_max),
i_r_squared(partAnnulus.i_r_squared),
o_r_squared(partAnnulus.o_r_squared),
normal_up(partAnnulus.normal_up) 
{}

PartAnnulus* PartAnnulus::clone(void) const 
{
	return new PartAnnulus(*this);
}

PartAnnulus& PartAnnulus::operator=(const PartAnnulus& rhs) 
{
	if (this == &rhs)
		return *this;

	GeometryObject::operator=(rhs);

	y = rhs.y;
	inner_radius = rhs.inner_radius;
	outer_radius = rhs.outer_radius;
	phi_min = rhs.phi_min;
	phi_max = rhs.phi_max;
	i_r_squared = rhs.i_r_squared;
	o_r_squared = rhs.o_r_squared;
	normal_up = rhs.normal_up;

	return *this;
}

PartAnnulus::~PartAnnulus(void)
{
	delete material_ptr;
}

bool PartAnnulus::hit(const Ray& ray, double& tmin, ShadeRec& sr) const 
{
	float t = (y - ray.o.y) / ray.d.y;

	if (t <= kEpsilon)
		return false;

	Point3D p = ray.o + t * ray.d;

	if (i_r_squared < p.d_squared(Point3D(0, y, 0)) && p.d_squared(Point3D(0, y, 0)) < o_r_squared)
	{
		double phi = atan2(p.x, p.z);
		if (phi < 0.0)
			phi += TWO_PI;

		if (phi_min <= phi && phi <= phi_max)
		{
			tmin = t;
			sr.normal = Normal(0.0, 1.0, 0.0);
			if (!normal_up)
				sr.normal.y *= -1;

			sr.local_hit_point = p;

			return true;
		}
	}

	return false;
}

bool PartAnnulus::shadow_hit(const Ray& ray, float& tmin) const 
{
	if (!shadows)
		return false;

	float t = (y - ray.o.y) / ray.d.y;

	if (t <= kEpsilon)
		return false;

	Point3D p = ray.o + t * ray.d;

	if (i_r_squared < p.d_squared(Point3D(0, y, 0)) && p.d_squared(Point3D(0, y, 0)) < o_r_squared)
	{
		double phi = atan2(p.x, p.z);
		if (phi < 0.0)
			phi += TWO_PI;

		if (phi_min <= phi && phi <= phi_max) 
		{
			tmin = t;
			return true;
		}
	}

	return false;
}