#ifndef __BRDF__
#define __BRDF__

#include "RGBColor.h"
#include "ShadeRec.h"
#include "Vector3D.h"
#include "Sampler.h"

class BRDF
{
public:

	BRDF();

	virtual ~BRDF();

	void set_sampler(Sampler* sPtr);
	
	virtual RGBColor f(const ShadeRec& sr,const Vector3D& wo,const Vector3D& wi)const = 0;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo,Vector3D& wi)const = 0; 

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const = 0;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo)const = 0;

protected:

	Sampler* sampler_ptr;
};

#endif