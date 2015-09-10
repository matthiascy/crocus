#include "SV_Lambertian.h"
#include "Constants.h"

SV_Lambertian::SV_Lambertian()
:BRDF(),kd(0),cd(NULL)
{}

SV_Lambertian::~SV_Lambertian()
{}


void SV_Lambertian::set_kd(const float kd)
{
	this->kd = kd;
}

void SV_Lambertian::set_cd(Texture* tex)
{
	cd = tex;
}

RGBColor SV_Lambertian::f(const ShadeRec &sr,const Vector3D &wo,const Vector3D &wi) const
{
	return (kd * cd->get_color(sr) * invPI);
}

RGBColor SV_Lambertian::sample_f(const ShadeRec &sr,const Vector3D &wo,Vector3D &wi) const
{
	return RGBColor();
}

RGBColor SV_Lambertian::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf)const
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

	return (kd * cd->get_color(sr) * invPI);
}

RGBColor SV_Lambertian::rho(const ShadeRec &sr, const Vector3D &wo) const
{
	return (kd * cd->get_color(sr));
}
