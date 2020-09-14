#include "Compound.h"
#include "Constants.h"

Compound::Compound()
:GeometryObject()
{}

Compound::~Compound()
{
	delete_objects();
}


void Compound::add_object(GeometryObject *object_ptr)
{
	objects.push_back(object_ptr);
}

void Compound::delete_objects()
{
	int num_objects = objects.size();

	for(int i = 0;i < num_objects;i++)
	{
		delete objects[i];
		objects[i] = NULL;
	}

	objects.erase(objects.begin(),objects.end());
}


bool Compound::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
	double t;
	Normal normal;
	Point3D local_hit_point;
	bool hit = false;
	tmin = kHugeValue;
	int num_objects = objects.size();

	for(int j = 0; j < num_objects; j++)
	{
		if( objects[j]->hit(ray, t ,sr) && (t<tmin))
		{
			hit  = true;
			tmin = t;

			if(objects[j]->get_material())
			{
				material_ptr = objects[j]->get_material();
			}
			normal = sr.normal;
			local_hit_point = sr.local_hit_point;
		}
	}
	if(hit)
	{
		sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}

	return hit;
}

bool Compound::shadow_hit(const Ray& ray,float& tmin)const
{
	float t;
	Normal normal;
	bool hit = false;
	tmin = kHugeValue;
	int num_objects = objects.size();

	for(int j = 0; j < num_objects; j++)
	{
		if( objects[j]->shadow_hit(ray,t) && (t<tmin))
		{
			hit  = true;
			tmin = t;
		}
	}
	return hit;
}