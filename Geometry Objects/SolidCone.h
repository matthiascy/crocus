#ifndef __SOLIDCONE__
#define __SOLIDCONE__

#include "Compound.h"
#include "OpenCone.h"
#include "Disk.h"

class SolidCone: public Compound 
{

public:

	SolidCone(void);

	SolidCone(double h, double r);

	SolidCone(const SolidCone& sc);

	virtual SolidCone* clone (void) const;

	SolidCone& operator= (const SolidCone& rhs);

	virtual ~SolidCone(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

	virtual bool shadow_hit(const Ray& ray, float& tmin) const;
};

#endif 