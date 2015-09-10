#pragma once

#include "GeometryObject.h"
#include "Normal.h"
#include "Point3D.h"

class Box:public GeometryObject
{
public:
	Box();
	Box(const Point3D& p0,const Point3D& p1);

	~Box();

	virtual bool hit(const Ray& r, double& tmin, ShadeRec& sr)const; 

	virtual bool shadow_hit(const Ray& ray,float& tmin)const; 

	Normal get_normal(const int face_hit) const;

	virtual BBox get_bounding_box()const;


private:
	double x0,y0,z0,x1,y1,z1;
	static const double kEpsilon;
};