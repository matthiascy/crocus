#ifndef __LAMBERTIAN__
#define __LAMBERTIAN__

#include "BRDF.h"

class Lambertian: public BRDF
{
public:
	Lambertian();
	~Lambertian();


	void set_kd(const float kd);

	void set_cd(const float r, const float g, const float b);

	void set_cd(const RGBColor&	c);

	virtual RGBColor f(const ShadeRec& sr,const Vector3D& wo,const Vector3D& wi)const; 

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo,Vector3D& wi)const; 

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;

	virtual RGBColor rho(const ShadeRec& sr,const Vector3D& wo)const;

private:
	float kd;
	RGBColor cd;
};

#endif