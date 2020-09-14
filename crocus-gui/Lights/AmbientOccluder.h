#ifndef __AMBIENT_OCCLUDER__
#define __AMBIENT_OCCLUDER__

#include "Light.h"
#include "Sampler.h"

class AmbientOccluder: public Light
{
public:

	AmbientOccluder(void);

	~AmbientOccluder(void);

	void set_sampler(Sampler* s_ptr);

	virtual Vector3D get_direction(const ShadeRec& sr);

	virtual bool in_shadow(const Ray &ray,const ShadeRec& sr)const;

	virtual RGBColor L(const ShadeRec& sr); 

	void set_min_amount(float a);

private:

	Vector3D u,v,w;
	Sampler*	sampler_ptr;
	RGBColor min_amount;
};

#endif