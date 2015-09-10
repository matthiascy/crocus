#include "RoundRimmedBowl.h"
#include "ConcavePartSphere.h"
#include "ConvexPartSphere.h"
#include "Instance.h"
#include "Torus.h"

RoundRimmedBowl::RoundRimmedBowl(void):
Compound() 
{

	objects.push_back(new ConcavePartSphere(Point3D(), 0.9, 0, 360, 90, 180));
	objects.push_back(new ConvexPartSphere(Point3D(), 1.0, 0, 360, 90, 180));
	objects.push_back(new Torus(0.95, 0.05));
}

RoundRimmedBowl::RoundRimmedBowl(double i_r, double o_r, const Point3D& c):
Compound()
{

	objects.push_back(new ConcavePartSphere(c, i_r, 0, 360, 90, 180));
	objects.push_back(new ConvexPartSphere(c, o_r, 0, 360, 90, 180));

	Instance* round_ptr = new Instance(new Torus((i_r + o_r) / 2.0, (o_r - i_r) / 2.0));
	round_ptr->translate(c.x, c.y, c.z);

	objects.push_back(round_ptr);
}

RoundRimmedBowl::RoundRimmedBowl(const RoundRimmedBowl& b):
Compound(b) 
{}

RoundRimmedBowl* RoundRimmedBowl::clone(void) const
{
	return new RoundRimmedBowl(*this);
}

RoundRimmedBowl& RoundRimmedBowl::operator=(const RoundRimmedBowl& rhs)
{
	if (this == &rhs)
		return *this;

	Compound::operator=(rhs);

	return *this;
}

RoundRimmedBowl::~RoundRimmedBowl(void)
{}

bool RoundRimmedBowl::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	return Compound::hit(ray, tmin, sr);
}

bool RoundRimmedBowl::shadow_hit(const Ray& ray, float& tmin) const
{
	if (!shadows)
		return false;

	return Compound::shadow_hit(ray, tmin);
}