#include "GeometryObject.h"
#include <stddef.h>


GeometryObject::GeometryObject()
:color(),material_ptr(NULL),sampler_ptr(NULL),shadows(true)
{}

GeometryObject::~GeometryObject()
{
	if(material_ptr)
	{
		delete material_ptr;
		material_ptr  = NULL;
	}

	if (sampler_ptr) 
	{
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
}

Material* GeometryObject::get_material()const
{
	return material_ptr;
}

void GeometryObject::set_material(Material* mat_ptr)
{
	material_ptr = mat_ptr;
}

void GeometryObject::set_shadows(bool b)
{
	shadows = b;
}

bool GeometryObject::casts_shadows()
{
	return shadows;
}


bool GeometryObject::shadow_hit(const Ray &ray,float &tmin)const
{
	return false;
}


void GeometryObject::set_sampler(Sampler* sampler)
{
	sampler_ptr = sampler;
}

Point3D GeometryObject::sample()
{
	return Point3D();
}

float GeometryObject::pdf(const ShadeRec& sr)const
{
	return 1;
}


Normal GeometryObject::get_normal()
{
	return Normal();
}

Normal GeometryObject::get_normal(const Point3D& p)
{
	return Normal();
}

BBox GeometryObject::get_bounding_box()const
{
	return BBox();
}