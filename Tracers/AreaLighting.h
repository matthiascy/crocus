#ifndef __AREA_LIGHTING__
#define __AREA_LIGHTING__

#include "Tracer.h"

class AreaLighting:public Tracer
{
public:

	AreaLighting(void);

	AreaLighting(World* _world_ptr);

	virtual ~AreaLighting(void);

	virtual RGBColor trace_ray(Ray ray,int depth)const;
};

#endif