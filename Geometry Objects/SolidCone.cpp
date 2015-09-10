#include "SolidCone.h"
#include "Maths.h"
#include "Material.h"

SolidCone::SolidCone(void):
Compound()
{

	add_object(new OpenCone);
	add_object(new Disk(Point3D(0.0, -1.0, 0.0), Normal(0.0, -1.0, 0.0), 1.0));
	add_object(new Disk(Point3D(0.0, 1.0, 0.0), Normal(0.0, 1.0, 0.0), 1.0));
}

SolidCone::SolidCone(double h, double r):
Compound() 
{

	add_object(new OpenCone(h, r));
	add_object(new Disk(Point3D(0.0, 0.0, 0.0), Normal(0.0, -1.0, 0.0), r));
}

SolidCone::SolidCone(const SolidCone& sc):
Compound(sc) 
{}

SolidCone* SolidCone::clone (void) const 
{
	return new SolidCone(*this);
}

SolidCone& SolidCone::operator=(const SolidCone& rhs) 
{
	if (this == &rhs)
		return *this;

	Compound::operator= (rhs);

	return *this;
}

SolidCone::~SolidCone(void) 
{}

bool SolidCone::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	return Compound::hit(ray, tmin, sr);
}

bool SolidCone::shadow_hit(const Ray& ray, float& tmin) const 
{
	if (!shadows)
		return false;

	return Compound::shadow_hit(ray, tmin);
}