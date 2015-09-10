#include "RayCast.h"
#include "ShadeRec.h"
#include "World.h"
#include "Material.h"


RayCast::RayCast(void)
:Tracer()
{}

RayCast::RayCast(World *_world_ptr)
:Tracer(_world_ptr)
{}

RayCast::~RayCast(void)
{}

RGBColor RayCast::trace_ray(Ray ray, int depth) const
{
	ShadeRec sr(world_ptr->hit_objects(ray));

	if(sr.hit_an_object)
	{
		sr.ray = ray;  // compute highlight 
		return sr.material_ptr->shade(sr);
	}
	else
		return world_ptr->background_color;
}