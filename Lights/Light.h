#ifndef __LIGHT__
#define __LIGHT__

#include "ShadeRec.h"
#include "RGBColor.h"
#include "Vector3D.h"
#include "Ray.h"

class Light
{
public:

	Light();

	~Light();

	virtual Vector3D get_direction(const ShadeRec& sr);

	virtual RGBColor L(const ShadeRec& sr);

	virtual bool in_shadow(const Ray& ray,const ShadeRec& sr)const;

	virtual void set_color(float r,float g,float b);

	virtual void scale_radiance(const float b);

	virtual float G(const ShadeRec& sr)const;

	virtual float pdf(const ShadeRec& sr)const;

	void set_shadows(bool b);

	bool casts_shadows();

protected:

	bool	shadows;
	float	ls;
	RGBColor	color;
};

#endif