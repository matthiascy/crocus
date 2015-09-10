#pragma once

#include "Tracer.h"


class RayCast:public Tracer
{
public:
	RayCast(void);

	RayCast(World* _world_ptr);

	virtual ~RayCast(void);

	virtual RGBColor trace_ray(Ray ray,int depth)const;
};
