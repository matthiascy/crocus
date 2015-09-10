#ifndef __TRIANGLE__
#define __TRIANGLE__


#include "GeometryObject.h"
#include "Point3D.h"
#include "Normal.h"


class Triangle:public GeometryObject
{
public:

	Triangle(void);

	Triangle(const Point3D& a ,const Point3D& b, const Point3D& c);

	~Triangle();

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray,float& tmin)const;

	virtual BBox get_bounding_box()const;

	virtual Normal get_normal();

public:

	Point3D		v0,v1,v2;
	Normal		normal;
	static const double kEpsilon;
};

#endif