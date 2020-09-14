#ifndef __POINT_LIGHT__
#define __POINT_LIGHT__

#include "Light.h"

class PointLight:public Light
{
public:

	PointLight();

	~PointLight();

	virtual Vector3D get_direction(const ShadeRec& sr); 

	virtual RGBColor L(const ShadeRec& sr);

	void set_location(double x,double y, double z);

	virtual bool in_shadow(const Ray& ray,const ShadeRec& sr)const;

private:

	Point3D		location;
};

#endif