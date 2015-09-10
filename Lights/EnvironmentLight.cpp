#include "EnvironmentLight.h"
#include "Emissive.h"
#include "World.h"
#include "Constants.h"


EnvironmentLight::EnvironmentLight()
:sampler_ptr(NULL),material_ptr(NULL),u(),v(),w(),wi()
{}

void EnvironmentLight::set_sampler(Sampler *s_ptr)
{
	if(sampler_ptr)
	{
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
	sampler_ptr = s_ptr;
	sampler_ptr->map_samples_to_hemisphere(1);
}

void EnvironmentLight::set_material(Material* m_ptr)
{
		if(material_ptr)
	{
		delete material_ptr;
		material_ptr = NULL;
	}
	material_ptr = m_ptr;

}

Vector3D EnvironmentLight::get_direction(const ShadeRec &sr) 
{
	w = sr.normal;
	v = Vector3D(0.0034,1,0.0071) ^ w;
	v.normalize();
	u = v ^ w;
	Point3D sp = sampler_ptr->sample_hemisphere();

	wi = sp.x * u + sp.y * v + sp.z * w;
	return wi;
}

RGBColor EnvironmentLight::L(const ShadeRec& sr)
{
	return (material_ptr->get_Le(sr));
}

bool EnvironmentLight::in_shadow(const Ray &ray, const ShadeRec &sr) const
{
	float t;
	int num_objects = sr.w.objects.size();

	bool in_shadow = false;

	for(int j = 0; j < num_objects; j++)
	{
		if(sr.w.objects[j]->casts_shadows())
		{	
			if(sr.w.objects[j]->shadow_hit(ray,t))
			{
				in_shadow = true;
			}

		}
				
	}
	return in_shadow;
}

float EnvironmentLight::pdf(const ShadeRec &sr) const
{
	float ndotw = sr.normal * wi;

	return ( ndotw / PI );
}