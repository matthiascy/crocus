#ifndef __MATERIAL__
#define __MATERIAL__

#include "RGBColor.h"
#include "ShadeRec.h"
#include "Sampler.h"

class Material
{
public:

	Material();

	~Material();

	virtual void set_sampler(Sampler* s);

	virtual RGBColor get_Le(const ShadeRec& sr)const;
	
	virtual RGBColor shade(ShadeRec& sr)const;

	virtual RGBColor area_light_shade(ShadeRec& sr)const;

	virtual RGBColor path_shade(ShadeRec& sr)const;

	virtual RGBColor global_shade(ShadeRec&	sr)const;
};

#endif