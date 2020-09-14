#include "GlobalTrace.h"
#include "World.h"
#include "Material.h"

GlobalTrace::GlobalTrace()
:Tracer()
{}

GlobalTrace::GlobalTrace(World *_world_ptr)
:Tracer(_world_ptr)
{}


GlobalTrace::~GlobalTrace()
{}

RGBColor GlobalTrace::trace_ray(Ray ray, int depth) const
{
	if(depth > world_ptr->vp.max_depth)
		return RGBColor();
	else
	{
		ShadeRec sr(world_ptr->hit_objects(ray));
		if(sr.hit_an_object)
		{
			sr.depth = depth;
			sr.ray = ray;

			return  (sr.material_ptr->global_shade(sr));
		}
		else
			return (world_ptr->background_color);
	}
}