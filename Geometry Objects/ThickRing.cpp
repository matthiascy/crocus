#include "ThickRing.h"
#include "ConvexCylinder.h"
#include "ConcaveCylinder.h"
#include "Maths.h"
#include "Material.h"
#include "Annulus.h"

ThickRing::ThickRing(void):
Compound()
{

	objects.push_back(new ConcaveCylinder(-1.0, 1.0, 0.5));
	objects.push_back(new ConvexCylinder);
	objects.push_back(new Annulus(Point3D(0.0, -1.0, 0.0), Normal(0.0, -1.0, 0.0), 0.5, 1.0));
	objects.push_back(new Annulus(Point3D(0.0, 1.0, 0.0), Normal(0.0, 1.0, 0.0), 0.5, 1.0));
}

ThickRing::ThickRing(const double bottom, const double top, const double r1, const double r2):
Compound()
{

	objects.push_back(new ConcaveCylinder(bottom, top, r1));
	objects.push_back(new ConvexCylinder(bottom, top, r2));
	objects.push_back(new Annulus(Point3D(0.0, bottom, 0.0), Normal(0.0, -1.0, 0.0), r1, r2));
	objects.push_back(new Annulus(Point3D(0.0, top, 0.0), Normal(0.0, 1.0, 0.0), r1, r2));
}

ThickRing::ThickRing(const ThickRing& sc):
Compound(sc)
{
}

ThickRing* ThickRing::clone (void) const
{
	return new ThickRing(*this);
}

ThickRing& ThickRing::operator=(const ThickRing& rhs) 
{
	if (this == &rhs)
		return *this;

	Compound::operator= (rhs);

	return *this;
}

ThickRing::~ThickRing(void)
{}

void ThickRing::set_inner_wall_material(Material* m)
{
	if (objects.size() >= 1 && objects[0])
	{
		objects[0]->set_material(m);
	}
}

void ThickRing::set_outer_wall_material(Material* m) 
{
	if (objects.size() >= 2 && objects[1])
	{
		objects[1]->set_material(m);
	}
}

void ThickRing::set_bottom_material(Material* m)
{
	if (objects.size() >= 3 && objects[2]) 
	{
		objects[2]->set_material(m);
	}
}

void ThickRing::set_top_material(Material* m) 
{
	if (objects.size() >= 4 && objects[3])
	{
		objects[3]->set_material(m);
	}
}

bool ThickRing::hit(const Ray& ray, double& tmin, ShadeRec& sr) const 
{
	return Compound::hit(ray, tmin, sr);
}

bool ThickRing::shadow_hit(const Ray& ray, float& tmin) const 
{
	if (!shadows)
		return false;

	return Compound::shadow_hit(ray, tmin);
}