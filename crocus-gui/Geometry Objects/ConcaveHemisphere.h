#ifndef __CONCAVE_HEMISPHERE__
#define __CONCAVE_HEMISPHERE__

#include "GeometryObject.h"
#include "Point3D.h"


class ConcaveHemisphere:public GeometryObject
{
public:

	ConcaveHemisphere(void);

	virtual ~ConcaveHemisphere(void);

	virtual	bool hit(const Ray& ray,double& tmin,ShadeRec &sr)const;

	virtual bool shadow_hit(const Ray& ray,float& tmin)const;

private:
	Point3D		center;
	double		radius;

};

#endif
