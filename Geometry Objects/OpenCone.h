#ifndef __OPENCONE__
#define __OPENCONE__

#include "GeometryObject.h"

class OpenCone: public GeometryObject 
{
public:

	OpenCone(void);

	OpenCone(double h, double r);

	OpenCone(const OpenCone& openCone);

	virtual OpenCone* clone(void) const;

	OpenCone& operator=(const OpenCone& rhs);

	virtual ~OpenCone(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

	virtual bool shadow_hit(const Ray& ray, float& tmin) const;

private:

	double height;
	double radius;
	double hr;
	double h2r2;
};

#endif 