#include "PointLight.h"
#include "Point3D.h"
#include "World.h"

PointLight::PointLight()
: Light() ,location()
{}

PointLight::~PointLight()
{}

void PointLight::set_location(double x,double y, double z)
{
	location = Point3D(x,y,z);
}

Vector3D PointLight::get_direction(const ShadeRec &sr)
{
	return ((location - sr.hit_point).hat());
}

RGBColor PointLight::L(const ShadeRec &sr)
{
	return ls * color;
}

bool PointLight::in_shadow(const Ray &ray, const ShadeRec &sr) const
{
	float t;
	int num_objects = sr.w.objects.size();
	float d = location.distance(ray.o);

	bool in_shadow = false;

	for(int j = 0; j < num_objects; j++)
	{
		if(sr.w.objects[j]->casts_shadows())
		{	
			if(sr.w.objects[j]->shadow_hit(ray,t) && t < d)
			{
				in_shadow = true;
			}

		}
				
	}
	return in_shadow;
}