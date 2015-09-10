#include "Transparent.h"
#include "World.h"
#include "Maths.h"


Transparent::Transparent()
:Phong(),reflective_brdf(new PerfectSpecular),specular_btdf(new PerfectTransmitter)
{}

Transparent::~Transparent()
{}

RGBColor Transparent::shade(ShadeRec& sr)const
{
	RGBColor L(Phong::shade(sr));

	Vector3D wo = -sr.ray.d;
	Vector3D wi;
	RGBColor fr = reflective_brdf->sample_f(sr,wo,wi);
	Ray reflected_ray(sr.hit_point,wi);

	if(specular_btdf->tir(sr))
		L += sr.w.tracer_ptr->trace_ray(reflected_ray, sr.depth + 1); 
	else
	{
		Vector3D wt;
		RGBColor ft = specular_btdf->sample_f(sr,wo,wt);
		Ray transmitted_ray(sr.hit_point,wt);

		L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray,sr.depth+1) * fabs(sr.normal * wi);
		L += ft * sr.w.tracer_ptr->trace_ray(transmitted_ray,sr.depth+1) * fabs(sr.normal * wi);
	}

	return L;
}