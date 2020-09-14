#ifndef __GLOBAL_TRACE__
#define __GLOBAL_TRACE__

#include "Tracer.h"

class GlobalTrace:public Tracer
{
public:

	GlobalTrace();

	GlobalTrace(World* _world_ptr);

	~GlobalTrace();

	virtual RGBColor trace_ray(Ray ray,int depth)const;
};

#endif