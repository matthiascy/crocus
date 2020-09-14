#ifndef __RAY__
#define __RAY__

#include "Vector3D.h"
#include "Point3D.h"

class Ray
{
public:
	Ray(void);
	Ray(const Point3D& _o,const Vector3D& _v);

	~Ray(void);

public:
	Vector3D d;
	Point3D o;
};


#endif
