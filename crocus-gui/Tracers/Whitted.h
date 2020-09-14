#ifndef __WITTED__
#define __WITTED__

#include "Tracer.h"


class Whitted:public Tracer
{
public:

	Whitted(void);

	Whitted(World* _world_ptr);

	virtual ~Whitted(void);

	virtual RGBColor trace_ray(Ray ray, int depth)const;

	virtual RGBColor trace_ray(Ray ray,double& tmin,const int depth)const;
};

#endif