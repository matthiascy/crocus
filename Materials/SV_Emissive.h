#ifndef __SV_EMISSIVE__
#define __SV_EMISSIVE__

#include "Material.h"
#include "Texture.h"


class SV_Emissive:public Material
{
public:

	SV_Emissive();

	~SV_Emissive();

	void scale_radiance(const float _ls);

	void set_ce(Texture* tex);

	virtual RGBColor get_Le(const ShadeRec& sr)const;
	
	virtual RGBColor shade(ShadeRec &sr)const;

	virtual RGBColor area_light_shade(ShadeRec& sr)const;

	virtual RGBColor path_shade(ShadeRec& sr)const;

	virtual RGBColor global_shade(ShadeRec&	sr)const;

private:

	float ls;
	Texture* ce;
};

#endif