#ifndef __MATTE__
#define __MATTE__

#include "Material.h"
#include "Lambertian.h"

class Matte:public Material
{
public:

	Matte();

	~Matte();

	void set_ka(const float k);

	void set_kd(const float k);

	void set_cd(const RGBColor& c);

	void set_cd(float r,float g,float b);

	void set_cd(float a);

	virtual void set_sampler(Sampler* s);

	virtual RGBColor shade(ShadeRec& sr)const;

	virtual RGBColor area_light_shade(ShadeRec& sr)const;

	virtual RGBColor path_shade(ShadeRec& sr)const;

	virtual RGBColor global_shade(ShadeRec&	sr)const;

private:
	Lambertian*		ambient_brdf; 
	Lambertian*		diffuse_brdf; 
};

#endif
