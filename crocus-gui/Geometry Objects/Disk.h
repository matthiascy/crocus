#ifndef __DISK__
#define __DISK__

#include "GeometryObject.h"
#include "Point3D.h"
#include "Normal.h"

class Disk: public GeometryObject
{
public:

	Disk();

	Disk(const Point3D& c,const Normal& n,const double r);

	Disk(Point3D c, float r, Normal n);

	~Disk();

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray,float& tmin)const;

private:

	Point3D		center;
	Normal		normal;
	double		radius;
	static const double kEpsilon;
};

#endif