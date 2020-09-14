#ifndef __SV_LAMBERTIAN__
#define __SV_LAMBERTIAN__

#include "BRDF.h"
#include "Texture.h"

class SV_Lambertian:public BRDF
{
public:

	SV_Lambertian();

	~SV_Lambertian();

	void set_kd(const float kd);

	void set_cd(Texture* tex);

	virtual RGBColor f(const ShadeRec& sr,const Vector3D& wo,const Vector3D& wi)const; 

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo,Vector3D& wi)const; 

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

	virtual RGBColor rho(const ShadeRec& sr,const Vector3D& wo)const;

private:

	float kd;
	Texture* cd;
};

#endif