#include "Lambertian.h"
#include "Constants.h"

Lambertian::Lambertian()
:BRDF(),kd(0),cd(1)
{}

Lambertian::~Lambertian()
{}


void Lambertian::set_kd(const float kd)
{
	this->kd = kd;
}

void Lambertian::set_cd(const float r, const float g, const float b)
{
	cd = RGBColor(r,g,b);
}

void Lambertian::set_cd(const RGBColor& c)
{
	cd = c;
}

RGBColor Lambertian::f(const ShadeRec &sr,const Vector3D &wo,const Vector3D &wi) const
{
	return (kd * cd * invPI);
}

RGBColor Lambertian::sample_f(const ShadeRec &sr,const Vector3D &wo,Vector3D &wi) const
{
	return RGBColor();
}

RGBColor Lambertian::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf)const
{
	Normal n(sr.normal);
	float ndotwo = n * wo;

	if(ndotwo < 0.0)
	{
		n = -n;
		ndotwo *= -1;
	}
	Vector3D w = n;
	Vector3D v = Vector3D(0.0034,1.0,0.0071) ^ w;
	v.normalize();
	Vector3D u = v ^ w;

	Point3D sp = sampler_ptr->sample_hemisphere();
	wi = sp.x * u + sp.y * v + sp.z * w;
	wi.normalize();

	pdf = sr.normal * wi * invPI;

	return (kd * cd * invPI);
}

RGBColor Lambertian::rho(const ShadeRec &sr, const Vector3D &wo) const
{
	return (kd * cd);
}
