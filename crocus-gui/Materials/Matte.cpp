#include "Matte.h"
#include "World.h"


Matte::Matte()
:Material(),ambient_brdf(new Lambertian),  diffuse_brdf(new Lambertian)
{}

Matte::~Matte()
{
	if(ambient_brdf)
	{
		delete ambient_brdf;
		ambient_brdf = NULL;
	}
	if(diffuse_brdf)
	{
		delete diffuse_brdf;
		diffuse_brdf = NULL;
	}
}


void Matte::set_ka(const float ka)
{
	ambient_brdf->set_kd(ka);
}

void Matte::set_kd(const float kd)
{
	diffuse_brdf->set_kd(kd);
}

void Matte::set_cd(const RGBColor &c)
{
	ambient_brdf->set_cd(c);
	diffuse_brdf->set_cd(c);
}


void Matte::set_cd(float r,float g, float b)
{
	ambient_brdf->set_cd(r,g,b);
	diffuse_brdf->set_cd(r,g,b);
}

void Matte::set_cd(float a)
{
	ambient_brdf->set_cd(a,a,a);
	diffuse_brdf->set_cd(a,a,a);
}

RGBColor Matte::shade(ShadeRec& sr)const
{
	Vector3D wo = -sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr,wo) * sr.w.ambient_ptr->L(sr);

	int numLights = sr.w.lights.size();

	for(int j = 0;j < numLights;j++)
	{
		Vector3D wi = sr.w.lights[j]->get_direction(sr);
		float ndotwi = sr.normal * wi; 

		if(ndotwi> 0.0) 
		{
			bool in_shadow = false;
			
			if(sr.w.lights[j]->casts_shadows())
			{
				Ray shadowRay(sr.hit_point,wi);
				in_shadow = sr.w.lights[j]->in_shadow(shadowRay,sr);
			}
			
			if(!in_shadow)
				L += diffuse_brdf->f(sr,wo,wi) * sr.w.lights[j]->L(sr) * ndotwi; 
		}
	}

	return L;
}

RGBColor Matte::area_light_shade(ShadeRec& sr)const
{
	Vector3D wo = -sr.ray.d;
	RGBColor L = ambient_brdf->rho(sr,wo) * sr.w.ambient_ptr->L(sr);

	int num_lights = sr.w.lights.size();

	for(int i = 0; i < num_lights; i++ )
	{
		Vector3D wi = sr.w.lights[i]->get_direction(sr);
		float ndotwi = sr.normal * wi;

		if( ndotwi > 0.0 )
		{
			bool in_shadow = false;

			if(sr.w.lights[i]->casts_shadows())
			{
				Ray shadow_ray(sr.hit_point,wi);
				in_shadow = sr.w.lights[i]->in_shadow(shadow_ray,sr);
			}

			if(!in_shadow)
			{
				L += diffuse_brdf->f(sr,wo,wi) * sr.w.lights[i]->L(sr) * sr.w.lights[i]->G(sr) * ndotwi / sr.w.lights[i]->pdf(sr); //和shade()函数就这一步不同，使用了MC采样
			}
		}
	}
	return L;
}

RGBColor Matte::path_shade(ShadeRec& sr)const
{
	Vector3D wi;
	Vector3D wo = -sr.ray.d;
	float pdf;
	RGBColor f = diffuse_brdf->sample_f(sr,wo,wi,pdf);
	float ndotwi = sr.normal * wi;
	Ray reflected_ray(sr.hit_point,wi);

	return (f * sr.w.tracer_ptr->trace_ray(reflected_ray,sr.depth+1) * ndotwi / pdf);
}


RGBColor Matte::global_shade(ShadeRec&	sr)const
{
	RGBColor L;

	if( sr.depth == 0 )
		L = area_light_shade(sr);

	Vector3D wi;
	Vector3D wo = -sr.ray.d;
	float pdf;
	RGBColor f = diffuse_brdf->sample_f(sr,wo,wi,pdf);
	float ndotwi = sr.normal * wi;
	Ray reflected_ray(sr.hit_point,wi);
	L += (f * sr.w.tracer_ptr->trace_ray(reflected_ray,sr.depth+1) * ndotwi / pdf);

	return L;
}

void Matte::set_sampler(Sampler* s)
{
	diffuse_brdf->set_sampler(s);
}