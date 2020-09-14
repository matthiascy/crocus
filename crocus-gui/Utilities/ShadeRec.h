#ifndef __SHADEREC__
#define __SHADEREC__

#include "RGBColor.h"
#include "Point3D.h"
#include "Normal.h"
#include "Ray.h"

class World;
class Material;

class ShadeRec
{
public:
	//ShadeRec(void);
	ShadeRec(World& _w);
	ShadeRec(const ShadeRec& sr);

	


	~ShadeRec(void);

public:
	bool		hit_an_object;
	float		t;
	RGBColor	color;
	Normal		normal;
	Point3D		hit_point;
	Point3D		local_hit_point;
	float		u;
	float		v;
	World&		w;
	Material*	material_ptr;
	Ray			ray;
	int			depth;

};

#endif