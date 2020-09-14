#include "Reflective.h"
#include "World.h"

Reflective::Reflective (void)
	:	Phong(),
		reflective_brdf(new PerfectSpecular)
{}

Reflective::Reflective(const Reflective& rm)
	: 	Phong(rm) {
	
	if(rm.reflective_brdf)
		reflective_brdf = rm.reflective_brdf->clone(); 
	else  
		reflective_brdf = NULL;
}


Reflective& Reflective::operator= (const Reflective& rhs) 
{
	if (this == &rhs)
		return (*this);
		
	Phong::operator=(rhs);
	
	if (reflective_brdf) 
	{
		delete reflective_brdf;
		reflective_brdf = NULL;
	}

	if (rhs.reflective_brdf)
		reflective_brdf = rhs.reflective_brdf->clone();

	return (*this);
}

Reflective*	Reflective::clone(void) const 
{
	return (new Reflective(*this));
}	

Reflective::~Reflective(void) 
{
	if (reflective_brdf) 
	{
		delete reflective_brdf;
		reflective_brdf = NULL;
	}
}


RGBColor Reflective::shade(ShadeRec& sr) const
{
	RGBColor L(Phong::shade(sr));  // direct illumination
	
	Vector3D wo = -sr.ray.d;
	Vector3D wi;	
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi); 
	Ray reflected_ray(sr.hit_point, wi); 
	
	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi);
					
	return (L);
}


RGBColor Reflective::area_light_shade(ShadeRec&	sr)const
{
	RGBColor L(Phong::shade(sr));  // direct illumination
	
	Vector3D wo = -sr.ray.d;
	Vector3D wi;	
	RGBColor fr = reflective_brdf->sample_f(sr, wo, wi); 
	Ray reflected_ray(sr.hit_point, wi); 
	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1) * (sr.normal * wi);
					
	return (L);
}

RGBColor Reflective::path_shade(ShadeRec& sr)const
{
	Vector3D wi;
	Vector3D wo = -sr.ray.d;
	float pdf;
	RGBColor f = reflective_brdf->sample_f(sr,wo,wi,pdf);
	float ndotwi = sr.normal * wi;
	Ray reflected_ray(sr.hit_point,wi);

	return (f * sr.w.tracer_ptr->trace_ray(reflected_ray,sr.depth+1) * ndotwi / pdf);
}

RGBColor Reflective::global_shade(ShadeRec&	sr)const
{
	RGBColor L;
	if( sr.depth == 0 )
		L = area_light_shade(sr);

	Vector3D wi;
	Vector3D wo = -sr.ray.d;
	float pdf;
	RGBColor f = reflective_brdf->sample_f(sr,wo,wi,pdf);
	float ndotwi = sr.normal * wi;

	Ray reflected_ray(sr.hit_point,wi);

	L += (f * sr.w.tracer_ptr->trace_ray(reflected_ray,sr.depth+1) * ndotwi / pdf);

	return L;
}