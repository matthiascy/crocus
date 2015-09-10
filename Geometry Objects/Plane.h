#ifndef __PLANE__
#define __PLANE__

#include "GeometryObject.h"
#include "Normal.h"

class Point3D;
class Ray;

class Plane : public GeometryObject
{
public:

	Plane(void);

	Plane(const Point3D& p, const Normal& n);

	~Plane(void);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray,float& tmin)const;

private:

	Point3D		point;
	Normal		normal;
	static const double kEpsilon;
};

#endif