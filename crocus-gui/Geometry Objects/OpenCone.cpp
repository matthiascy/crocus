#include "OpenCone.h"
#include "Maths.h"
#include "Material.h"
#include <math.h>

OpenCone::OpenCone(void):
GeometryObject(),
height(2.0),
radius(1.0),
hr(2.0),
h2r2(4.0) 
{}

OpenCone::OpenCone(double h, double r):
GeometryObject(),
height(h),
radius(r),
hr(height / radius),
h2r2((height * height) / (radius * radius)) 
{}

OpenCone::OpenCone(const OpenCone& openCone):
GeometryObject(openCone),
height(openCone.height),
radius(openCone.radius),
hr(openCone.hr),
h2r2(openCone.h2r2) 
{}

OpenCone* OpenCone::clone(void) const 
{
	return new OpenCone(*this);
}

OpenCone& OpenCone::operator=(const OpenCone& rhs)
{
	if (this == &rhs)
		return *this;

	GeometryObject::operator=(rhs);

	height = rhs.height;
	radius = rhs.radius;
	hr = rhs.hr;
	h2r2 = rhs.h2r2;

	return *this;
}

OpenCone::~OpenCone(void)
{
	delete material_ptr;
}

bool OpenCone::hit(const Ray& ray, double& tmin, ShadeRec& sr) const 
{
	double t;
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;

	double a = h2r2 * (dx * dx + dz * dz) - dy * dy;
	double b = 2 * (h2r2 * (ox * dx + oz * dz) + dy * (height - oy));
	double c = h2r2 * (ox * ox + oz * oz) + 2 * oy * height - oy * oy - height * height;
	double disc = b * b - 4.0 * a * c;

	if (disc < 0.0)
		return false;
	else 
	{
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom; // smaller root

		if (t > kEpsilon)
		{
			double yhit = oy + t * dy;

			if (0 <= yhit && yhit <= height) 
			{
				tmin = t;
				sr.normal = Normal(hr * (ox + t * dx), oy + t * dy - height, hr * (oz + t * dz));
				sr.normal.normalize();

				sr.local_hit_point = ray.o + tmin * ray.d;

				return true;
			}
		}

		t = (-b + e) / denom; // larger root

		if (t > kEpsilon) 
		{
			double yhit = oy + t * dy;

			if (0 <= yhit && yhit <= height)
			{
				tmin = t;
				sr.normal = Normal(hr * (ox + t * dx), - oy - t * dy + height, hr * (oz + t * dz));
				sr.normal.normalize();

				// test for hitting inside surface

				if (-ray.d * sr.normal < 0.0)
					sr.normal = -sr.normal;

				sr.local_hit_point = ray.o + tmin * ray.d;

				return true;
			}
		}
	}

	return false;
}

bool OpenCone::shadow_hit(const Ray& ray, float& tmin) const 
{
	if (!shadows)
		return false;

	double t;
	double ox = ray.o.x;
	double oy = ray.o.y;
	double oz = ray.o.z;
	double dx = ray.d.x;
	double dy = ray.d.y;
	double dz = ray.d.z;

	double a = h2r2 * (dx * dx + dz * dz) - dy * dy;
	double b = 2 * (h2r2 * (ox * dx + oz * dz) + dy * (height - oy));
	double c = h2r2 * (ox * ox + oz * oz) + 2 * oy * height - oy * oy - height * height;
	double disc = b * b - 4.0 * a * c;

	if (disc < 0.0)
		return false;
	else 
	{
		double e = sqrt(disc);
		double denom = 2.0 * a;
		t = (-b - e) / denom; // smaller root

		if (t > kEpsilon) 
		{
			double yhit = oy + t * dy;

			if (0 <= yhit && yhit <= height) 
			{
				tmin = t;
				return true;
			}
		}

		t = (-b + e) / denom; // larger root

		if (t > kEpsilon)
		{
			double yhit = oy + t * dy;

			if (0 <= yhit && yhit <= height)
			{
				tmin = t;
				return true;
			}
		}
	}

	return false;
}