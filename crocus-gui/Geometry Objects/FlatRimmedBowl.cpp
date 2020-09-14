#include "FlatRimmedBowl.h"
#include "ConcavePartSphere.h"
#include "ConvexPartSphere.h"
#include "Annulus.h"

FlatRimmedBowl::FlatRimmedBowl(void):
Compound() 
{

	objects.push_back(new ConcavePartSphere(Point3D(), 0.9, 0, 360, 90, 180));
	objects.push_back(new ConvexPartSphere(Point3D(), 1.0, 0, 360, 90, 180));
	objects.push_back(new Annulus(Point3D(), Normal(0.0, 1.0, 0.0), 0.9, 1.0));
}

FlatRimmedBowl::FlatRimmedBowl(double i_r, double o_r, const Point3D& c):
Compound() 
{

	objects.push_back(new ConcavePartSphere(c, i_r, 0, 360, 90, 180));
	objects.push_back(new ConvexPartSphere(c, o_r, 0, 360, 90, 180));
	objects.push_back(new Annulus(c, Normal(0.0, 1.0, 0.0), i_r, o_r));
}

FlatRimmedBowl::FlatRimmedBowl(const FlatRimmedBowl& b):
Compound(b)
{
}

FlatRimmedBowl* FlatRimmedBowl::clone(void) const
{
	return new FlatRimmedBowl(*this);
}

FlatRimmedBowl& FlatRimmedBowl::operator=(const FlatRimmedBowl& rhs)
{
	if (this == &rhs)
		return *this;

	Compound::operator=(rhs);

	return *this;
}

FlatRimmedBowl::~FlatRimmedBowl(void) 
{
}

bool FlatRimmedBowl::hit(const Ray& ray, double& tmin, ShadeRec& sr) const
{
	return Compound::hit(ray, tmin, sr);
}

bool FlatRimmedBowl::shadow_hit(const Ray& ray, float& tmin) const
{
	if (!shadows)
		return false;

	return Compound::shadow_hit(ray, tmin);
}