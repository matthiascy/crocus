#include "AreaLighting.h"
#include "ShadeRec.h"
#include "World.h"
#include "Material.h"


AreaLighting::AreaLighting(void)
:Tracer()
{}

AreaLighting::AreaLighting(World *_world_ptr)
:Tracer(_world_ptr)
{}

AreaLighting::~AreaLighting(void)
{}


RGBColor AreaLighting::trace_ray(Ray ray, int depth) const
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

			return  (sr.material_ptr->area_light_shade(sr)); 
		}
		else
			return (world_ptr->background_color);
	}
}