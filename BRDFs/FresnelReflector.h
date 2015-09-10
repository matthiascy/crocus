#ifndef __FRESNEL_REFLECTOR__
#define __FRESNEL_REFLECTOR__

#include "BRDF.h"

class FresnelReflector:public BRDF
{
public:
	FresnelReflector();
	~FresnelReflector();

	virtual RGBColor f(const ShadeRec& sr,const Vector3D& wo,const Vector3D& wi)const; 

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo,Vector3D& wi)const; 

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo)const;

	float fresnel(const ShadeRec&	sr)const;

	void set_eta_in(const float e);

	void set_eta_out(const float e);

private:
	float kr;
	float eta_in,eta_out;
};


inline void FresnelReflector::set_eta_in(const float e)
{
	eta_in = e;
}

inline void FresnelReflector::set_eta_out(const float e)
{
	eta_out = e;
}

#endif