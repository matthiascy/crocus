#ifndef __AMBIENT__
#define __AMBIENT__

#include "Light.h"

class Ambient:public Light
{
public:

	Ambient();

	~Ambient();

	virtual Vector3D get_direction(const ShadeRec& sr);

	virtual RGBColor L(const ShadeRec& sr);

	virtual bool in_shadow(const Ray& ray,const ShadeRec& sr)const;


};

#endif