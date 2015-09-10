#include "FresnelTransmitter.h"
#include "Constants.h"
#include "Maths.h"

FresnelTransmitter::FresnelTransmitter()
:kt(1.0)
{}

FresnelTransmitter::~FresnelTransmitter()
{}

bool FresnelTransmitter::tir(const ShadeRec &sr)const
{
	Vector3D wo(-sr.ray.d);
	float cos_thetai = sr.normal * wo;
	float eta = eta_in / eta_out;
	if(cos_thetai < 0.0)
		eta = 1.0 / eta;

	return (1.0 - (1.0 - cos_thetai * cos_thetai) /(eta * eta) < 0.0);
}

RGBColor FresnelTransmitter::f(const ShadeRec &sr, const Vector3D &wt, const Vector3D &wo) const
{
	return RGBColor();
}

RGBColor FresnelTransmitter::sample_f(const ShadeRec &sr, const Vector3D &wo, Vector3D &wt) const
{
	Normal n(sr.normal);
	float cos_theta_i = n * wo;
	float eta = eta_in / eta_out;
	
	if(cos_theta_i < 0.0)
	{
		cos_theta_i *= -1;
		n = -n;
		eta = 1.0 / eta;
	}

	float temp = 1.0 - (1.0 - cos_theta_i * cos_theta_i) / ( eta * eta );
	float cos_theta2 = sqrt(temp);
	wt = -wo/ eta - (cos_theta2 - cos_theta_i / eta) * n;

	wt.normalize();

	return (fresnel(sr) * white / fabs(n * wt));
}

RGBColor FresnelTransmitter::sample_f(const ShadeRec &sr, const Vector3D &wo, Vector3D &wt, float &pdf) const
{
	return RGBColor();
}

RGBColor FresnelTransmitter::rho(const ShadeRec &sr, const Vector3D &wo) const
{
	return RGBColor();
}

float FresnelTransmitter::fresnel(const ShadeRec &sr) const
{
	Normal normal(sr.normal);
	float ndotd = -normal * sr.ray.d;
	float eta;
	
	if (ndotd < 0.0) { 
		normal = -normal;
		eta = eta_out / eta_in;
	}
	else
		eta = eta_in / eta_out;

	float cos_theta_i 		= -normal * sr.ray.d; 
	float temp 				= 1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta);
	float cos_theta_t 		= sqrt (1.0 - (1.0 - cos_theta_i * cos_theta_i) / (eta * eta));
	float r_parallel 		= (eta * cos_theta_i - cos_theta_t) / (eta * cos_theta_i + cos_theta_t);
	float r_perpendicular 	= (cos_theta_i - eta * cos_theta_t) / (cos_theta_i + eta * cos_theta_t);
	float kr 				= 0.5 * (r_parallel * r_parallel + r_perpendicular * r_perpendicular);
			
	return (1.0 - kr);
}