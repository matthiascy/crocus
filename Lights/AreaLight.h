#ifndef __AREA_LIGHT__
#define __AREA_LIGHT__

#include "Light.h"
#include "GeometryObject.h"
#include "Point3D.h"
#include "Normal.h"
#include "Vector3D.h"

class AreaLight : public Light
{
public:

	AreaLight();

	~AreaLight();

	virtual Vector3D get_direction(const ShadeRec& sr); 

	virtual bool in_shadow(const Ray& ray, const ShadeRec& sr)const;

	virtual RGBColor L(const ShadeRec& sr);

	virtual float G(const ShadeRec& sr)const;

	virtual float pdf(const ShadeRec& sr)const;

	void set_object(GeometryObject* _optr);

private:

	GeometryObject* object_ptr;
	Material* material_ptr;
	Point3D sample_point;
	Normal light_normal;
	Vector3D wi;
};

#endif