#ifndef __GEOMETRY_OBJECT__
#define __GEOMETRY_OBJECT__

#include "Ray.h"
#include "ShadeRec.h"
#include "RGBColor.h"
#include "Normal.h"
#include "Point3D.h"
#include "Sampler.h"
#include "BBox.h"


class Material;

class GeometryObject
{

public:

	GeometryObject();

	virtual ~GeometryObject();

	void set_color(float r, float g, float b);

	Material* get_material()const;

	void	set_material(Material* mat_ptr);

	virtual bool hit(const Ray& r, double& tmin, ShadeRec& sr)const = 0; 

	virtual bool shadow_hit(const Ray& ray,float& tmin)const;  
	
	virtual void set_sampler(Sampler* sampler); 

	virtual Point3D sample(void);

	virtual float pdf(const ShadeRec& sr)const;

	virtual Normal get_normal(const Point3D& p);

	virtual BBox get_bounding_box()const;

	virtual Normal get_normal();

	void set_shadows(bool b);

	bool casts_shadows();

public:

	RGBColor		color;
	mutable Material*		material_ptr;  
	bool	shadows;
	
protected:

	Sampler*		sampler_ptr;	

};

inline void GeometryObject::set_color(float r, float g, float b)
{
	color = RGBColor(r,g,b);
}

#endif
