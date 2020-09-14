#ifndef __BTDF__
#define __BTDF__

#include "RGBColor.h"
#include "ShadeRec.h"
#include "Vector3D.h"
#include "Sampler.h"

class BTDF
{

public:

	BTDF();

	virtual ~BTDF();

	void set_sampler(Sampler* sPtr);

	virtual RGBColor f(const ShadeRec& sr,const Vector3D& wt,const Vector3D& wo)const = 0;

	virtual RGBColor sample_f(const ShadeRec& sr,const Vector3D& wo,Vector3D& wt)const = 0;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt, float& pdf) const = 0;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo)const = 0;

	virtual bool tir(const ShadeRec& sr)const = 0;


protected:
	Sampler*	sampler_ptr;

};

#endif