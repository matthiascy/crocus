#ifndef __ROUNDRIMMEDBOWL__
#define __ROUNDRIMMEDBOWL__

#include "Compound.h"

class RoundRimmedBowl: public Compound 
{

public:

	RoundRimmedBowl(void);

	RoundRimmedBowl(double i_r, double o_r, const Point3D& c = Point3D());

	RoundRimmedBowl(const RoundRimmedBowl& b);

	virtual RoundRimmedBowl* clone(void) const;

	virtual RoundRimmedBowl& operator= (const RoundRimmedBowl& rhs);

	virtual ~RoundRimmedBowl(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

	virtual bool shadow_hit(const Ray& ray, float& tmin) const;
};

#endif 