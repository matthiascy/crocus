#include "Directional.h"
#include "World.h"	

Directional::Directional(void)
	: 	Light(),
		dir(0, 1, 0)			
{}

Directional::Directional(const Directional& dl)
	: 	Light(dl),
		dir(dl.dir)  		
{}

Directional& Directional::operator= (const Directional& rhs) 	
{
	if (this == &rhs)
		return (*this);
			
	Light::operator= (rhs);
	
	dir 	= rhs.dir;

	return (*this);
}

Directional::~Directional(void) {}


Vector3D Directional::get_direction(const ShadeRec& sr)
{
	return (dir);
}	

RGBColor Directional::L(const ShadeRec& s) 
{	
	return (ls * color);
}

bool Directional::in_shadow(const Ray &ray, const ShadeRec &sr) const
{
	float t;
	int num_objects = sr.w.objects.size();

	bool in_shadow = false;

	for(int j = 0; j < num_objects; j++)
	{
		if(sr.w.objects[j]->casts_shadows())
		{	
			if(sr.w.objects[j]->shadow_hit(ray,t))
			{
				in_shadow = true;
			}

		}
				
	}
	return in_shadow;
}


