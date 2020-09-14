#include "Tracer.h"

Tracer::Tracer()
{}


Tracer::Tracer(World* _world_ptr)
{
	world_ptr = _world_ptr;
}

Tracer::~Tracer()
{}


RGBColor Tracer::trace_ray(Ray ray,double& tmin,const int depth)const
{
	return RGBColor();
}

