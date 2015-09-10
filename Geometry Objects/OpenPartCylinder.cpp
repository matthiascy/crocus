#include "Constants.h"
#include "OpenPartCylinder.h"
#include "Material.h"
#include <math.h>


OpenPartCylinder::OpenPartCylinder (void):
GeometryObject(),
y0(-1.0),
y1(1.0),
radius(1.0),
phi_min(0.0), // in radians
phi_max(TWO_PI), // in radians
inv_radius(1.0)	
{}


OpenPartCylinder::OpenPartCylinder (const double bottom,
									const double top,
									const double radius,
									const double azimuth_min,	// in degrees
									const double azimuth_max):	// in degrees

GeometryObject(),
y0(bottom),
y1(top),
radius(radius),
phi_min(azimuth_min * PI_ON_180), // in radians
phi_max(azimuth_max * PI_ON_180), // in radians
inv_radius(1.0 / radius) 
{}


OpenPartCylinder::OpenPartCylinder(const double bottom, const double top, const double r):
GeometryObject(),
y0(bottom),
y1(top),
radius(r),
phi_min(0.0),
phi_max(TWO_PI),
inv_radius(1.0 / radius)
{}


OpenPartCylinder* OpenPartCylinder::clone(void) const 
{
	return new OpenPartCylinder(*this);
}


OpenPartCylinder::OpenPartCylinder (const OpenPartCylinder& ps):
GeometryObject(ps),
y0(ps.y0),
y1(ps.y1),
radius(ps.radius),
phi_min(ps.phi_min),
phi_max(ps.phi_max),
inv_radius(ps.inv_radius) 
{}


OpenPartCylinder& OpenPartCylinder::operator= (const OpenPartCylinder& rhs)
{
	if (this == &rhs)
		return *this;

	GeometryObject::operator=(rhs);

	y0 = rhs.y0;
	y1 = rhs.y1;
	radius = rhs.radius;
	phi_min = rhs.phi_min;
	phi_max = rhs.phi_max;
	inv_radius = rhs.inv_radius;

	return *this;
}


OpenPartCylinder::~OpenPartCylinder(void) 
{
	delete material_ptr;
}


bool OpenPartCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	double t;
	double ox = ray.o.x;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dz = ray.d.z;

	double a = dx * dx + dz * dz;
	double b = 2.0 * (ox * dx + oz * dz);
	double c = ox * ox + oz * oz - radius * radius;
	double disc = b * b - 4.0 * a * c ;

	if (disc < 0.0)
		return false;
	else {
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom; // smaller root

		if (t > kEpsilon) 
		{
			Vector3D hit = ray.o + t * ray.d;

			double phi = atan2(hit.x, hit.z);
			if (phi < 0.0)
				phi += TWO_PI;

			if (y0 <= hit.y && hit.y <= y1 && phi_min <= phi && phi <= phi_max) 
			{
				tmin = t;
				sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);

				// test for hitting inside surface
				if (-ray.d * sr.normal < 0.0)
					sr.normal = -sr.normal; // points towards camera

				sr.local_hit_point = ray.o + tmin * ray.d;
				return true;
			}
		}

		t = (-b + e) / denom; // larger root

		if (t > kEpsilon)
		{
			Vector3D hit = ray.o + t * ray.d;

			double phi = atan2(hit.x, hit.z);
			if (phi < 0.0)
				phi += TWO_PI;

			if (y0 <= hit.y && hit.y <= y1 && phi_min <= phi && phi <= phi_max) 
			{
				tmin = t;
				sr.normal = - Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);

				// test for hitting inside surface
				if (-ray.d * sr.normal < 0.0)
					sr.normal = -sr.normal; // points towards camera

				sr.local_hit_point = ray.o + tmin * ray.d;
				return true;
			}
		}
	}

	return false;
}

bool OpenPartCylinder::shadow_hit(const Ray& ray, float& tmin) const 
{
	if (!shadows)
		return false;

	double t;
	double ox = ray.o.x;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dz = ray.d.z;

	double a = dx * dx + dz * dz;
	double b = 2.0 * (ox * dx + oz * dz);
	double c = ox * ox + oz * oz - radius * radius;
	double disc = b * b - 4.0 * a * c ;

	if (disc < 0.0)
		return false;
	else
	{
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom; // smaller root

		if (t > kEpsilon) {
			Vector3D hit = ray.o + t * ray.d;

			double phi = atan2(hit.x, hit.z);
			if (phi < 0.0)
				phi += TWO_PI;

			if (y0 <= hit.y && hit.y <= y1 && phi_min <= phi && phi <= phi_max)
			{
				tmin = t;
				return true;
			}
		}

		t = (-b + e) / denom; // larger root

		if (t > kEpsilon) 
		{
			Vector3D hit = ray.o + t * ray.d;

			double phi = atan2(hit.x, hit.z);
			if (phi < 0.0)
				phi += TWO_PI;

			if (y0 <= hit.y && hit.y <= y1 && phi_min <= phi && phi <= phi_max)
			{
				tmin = t;
				return true;
			}
		}
	}

	return false;
}