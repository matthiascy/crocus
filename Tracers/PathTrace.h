#ifndef __PATH_TRACE__
#define __PATH_TRACE__

#include "Tracer.h"

class PathTrace:public Tracer
{
public:

	PathTrace();

	PathTrace(World* _world_ptr);

	~PathTrace();

	virtual RGBColor trace_ray(Ray ray,int depth)const;
};

#endif