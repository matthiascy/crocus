#ifndef __ENVIRONMENT_LIGHT__
#define __ENVIRONMENT_LIGHT__

#include "Light.h"
#include "Sampler.h"
#include "Material.h"
#include "Vector3D.h"

class EnvironmentLight:public Light
{
public:

	EnvironmentLight();

	~EnvironmentLight();

	void set_sampler(Sampler* sampler);

	void set_material(Material* m_ptr);

	virtual Vector3D get_direction(const ShadeRec& sr); 

	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr)const;

	virtual RGBColor L(const ShadeRec& sr);

	virtual float pdf(const ShadeRec& sr)const;

private:

	Sampler*	sampler_ptr;
	Material*	material_ptr;
	Vector3D	u,v,w;
	Vector3D	wi;
};
#endif
