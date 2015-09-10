#ifndef __SPHERE__
#define __SPHERE__

#include "GeometryObject.h"
#include "Point3D.h"


class Sphere:public GeometryObject
{
public:

	Sphere(void);

	Sphere(const Point3D& p,const double r);

	virtual ~Sphere(void);

	virtual	bool hit(const Ray& ray,double& tmin,ShadeRec &sr)const;

	virtual bool shadow_hit(const Ray& ray,float& tmin)const;

	virtual BBox get_bounding_box()const;

	void  set_radius(const float r);

	void  set_center(const Point3D c);

	void  set_center(const float x,const float y, const float z);

protected:

	Point3D		center;
	double		radius;
};

#endif
