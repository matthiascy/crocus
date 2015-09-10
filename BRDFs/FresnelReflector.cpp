#include "FresnelReflector.h"
#include "Constants.h"
#include "Maths.h"


FresnelReflector::FresnelReflector()
:BRDF(),kr(0)
{}

FresnelReflector::~FresnelReflector()
{}



RGBColor FresnelReflector::f(const ShadeRec &sr,const Vector3D &wo,const Vector3D &wi) const
{
	return RGBColor();
}

RGBColor FresnelReflector::sample_f(const ShadeRec &sr,const Vector3D &wo,Vector3D &wi) const
{
	Normal n(sr.normal);
	float ndotwo = n * wo;
	if(ndotwo < 0.0)
	{
		n = -n;
		ndotwo *= -1;
	}

	wi = -wo + 2.0 * ndotwo * n; 
	wi.normalize();
	return (fresnel(sr) * white / fabs(n * wi)) ;
}

RGBColor FresnelReflector::sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf)const
{
	return RGBColor();
}

RGBColor FresnelReflector::rho(const ShadeRec &sr, const Vector3D &wo) const
{
	return RGBColor();
}

float FresnelReflector::fresnel(const ShadeRec &sr) const
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
			
	return (kr);
}
