#ifndef __TRACER__
#define __TRACER__

#include "Ray.h"
#include "RGBColor.h"
#include "Constants.h"

class World;

class Tracer
{
public:

	Tracer(void);

	Tracer(World* _world_ptr);

	virtual ~Tracer(void);

	virtual RGBColor trace_ray(Ray ray,int depth)const=0;

	virtual RGBColor trace_ray(Ray ray,double& tmin,const int depth)const;

protected:

	World*		world_ptr;

};

#endif
