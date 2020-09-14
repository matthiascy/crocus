#ifndef __EMISSIVE__
#define __EMISSIVE__

#include "Material.h"

class Emissive:public Material
{
public:

	Emissive();

	~Emissive();

	void scale_radiance(const float _ls);

	void set_ce(const float r,const float g,const float b);

	void set_ce(const RGBColor& c);

	virtual RGBColor get_Le(const ShadeRec& sr)const;
	
	virtual RGBColor shade(ShadeRec &sr)const;

	virtual RGBColor area_light_shade(ShadeRec& sr)const;

	virtual RGBColor path_shade(ShadeRec& sr)const;

	virtual RGBColor global_shade(ShadeRec&	sr)const;

private:

	float ls;
	RGBColor ce;
};

#endif