#include "PerfectTransmitter.h"

#include "Maths.h"

PerfectTransmitter::PerfectTransmitter()
:kt(1.),ior(1)
{}

PerfectTransmitter::~PerfectTransmitter()
{}

bool PerfectTransmitter::tir(const ShadeRec &sr)const
{
	Vector3D wo(-sr.ray.d);
	float cos_thetai = sr.normal * wo;
	float eta = ior;
	if(cos_thetai < 0.0)
		eta = 1.0 / eta;

	return (1.0 - (1.0 - cos_thetai * cos_thetai) /(eta * eta) < 0.0);
}

RGBColor PerfectTransmitter::f(const ShadeRec &sr, const Vector3D &wt, const Vector3D &wo) const
{
	return RGBColor();
}

RGBColor PerfectTransmitter::sample_f(const ShadeRec &sr, const Vector3D &wo, Vector3D &wt) const
{
	Normal n(sr.normal);
	float cos_theta_i = n * wo;
	float eta = ior;
	
	if(cos_theta_i < 0.0)
	{
		cos_theta_i *= -1;
		n = -n;
		eta = 1.0 / eta;
	}

	float temp = 1.0 - (1.0 - cos_theta_i * cos_theta_i) / ( eta * eta );
	float cos_theta2 = sqrt(temp);
	wt = -wo/ eta - (cos_theta2 - cos_theta_i / eta) * n;

	return ( kt / (eta * eta) * white / fabs(sr.normal * wt));
}

RGBColor PerfectTransmitter::sample_f(const ShadeRec &sr, const Vector3D &wo, Vector3D &wt, float &pdf) const
{
	return RGBColor();
}

RGBColor PerfectTransmitter::rho(const ShadeRec &sr, const Vector3D &wo) const
{
	return RGBColor();
}