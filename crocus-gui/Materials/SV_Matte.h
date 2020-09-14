#ifndef __SV_MATTE__
#define __SV_MATTE__

#include "Material.h"
#include "SV_Lambertian.h"
#include "Texture.h"

class SV_Matte:public Material
{
public:

	SV_Matte();

	~SV_Matte();


	void set_ka(const float k);

	void set_kd(const float k);

	void set_cd(Texture* tex);

	virtual void set_sampler(Sampler* s);

	virtual RGBColor shade(ShadeRec& sr)const;

	virtual RGBColor area_light_shade(ShadeRec& sr)const;

	virtual RGBColor path_shade(ShadeRec& sr)const;

	virtual RGBColor global_shade(ShadeRec&	sr)const;

private:
	SV_Lambertian*		ambient_brdf; 
	SV_Lambertian*		diffuse_brdf; 
};

#endif
