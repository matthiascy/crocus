#ifndef __ANNULUS__
#define __ANNULUS__

#include "GeometryObject.h"
#include "Point3D.h"
#include "Normal.h"

class Annulus:public GeometryObject
{
public:

	Annulus();

	Annulus(const Point3D& c,const Normal& n,const double r_in,const double r_out);

	~Annulus();

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray,float& tmin)const;

	//virtual BBox get_bounding_box()const;

private:

	Point3D		center;
	Normal		normal;
	double		inner_radius;
	double		outer_radius;
	static const double kEpsilon;
};

#endif