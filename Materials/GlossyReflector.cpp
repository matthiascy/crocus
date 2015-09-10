#include "GlossyReflector.h"
#include "World.h"


GlossyReflector::GlossyReflector()
:Phong(),glossy_specular_brdf(new GlossySpecular)
{}

GlossyReflector::~GlossyReflector()
{}

RGBColor GlossyReflector::area_light_shade(ShadeRec& sr)const
{
	RGBColor L(Phong::area_light_shade(sr));
	Vector3D wo(-sr.ray.d);
	Vector3D wi;
	float pdf;
	RGBColor fr(glossy_specular_brdf->sample_f(sr,wo,wi,pdf));
	Ray reflected_ray(sr.hit_point,wi);

	L += fr * sr.w.tracer_ptr->trace_ray(reflected_ray,sr.depth+1) * (sr.normal*wi) / pdf;

	return L;
}


