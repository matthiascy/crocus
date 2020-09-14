#include "PerfectSpecular.h"
#include "Constants.h"
#include "Maths.h"

PerfectSpecular::PerfectSpecular(void)
	: 	BRDF(),
		kr(0), 
		cr(1)
{}

PerfectSpecular::~PerfectSpecular(void) {}

PerfectSpecular* PerfectSpecular::clone(void) const 
{
	return (new PerfectSpecular(*this));
}	

RGBColor PerfectSpecular::f(const ShadeRec& sr, const Vector3D& wo, const Vector3D& wi) const 
{
	return (black);
}

// this computes wi: the direction of perfect mirror reflection
// it's called from from the functions Reflective::shade and Transparent::shade.
// the fabs in the last statement is for transparency

RGBColor PerfectSpecular::sample_f(const ShadeRec& sr,const Vector3D& wo,Vector3D& wi) const 
{
	Normal n(sr.normal);
	float ndotwo = n * wo;

	if(ndotwo < 0.0)
	{
		n = -n;
		ndotwo *= -1;
	}

	wi = -wo + 2.0 * ndotwo * n; 
	return (kr * cr / fabs(sr.normal * wi)); 
}											 

RGBColor PerfectSpecular::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const 
{
	Normal n(sr.normal);
	float ndotwo = n * wo;

	if(ndotwo < 0.0)
	{
		n = -n;
		ndotwo *= -1;
	}
	wi = -wo + 2.0  * ndotwo * n; 
	pdf = fabs(sr.normal * wi);
	return (kr * cr);  
}

RGBColor PerfectSpecular::rho(const ShadeRec& sr, const Vector3D& wo) const 
{
	return (black);
}

