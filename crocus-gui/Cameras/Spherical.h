#ifndef __SPHERICAL__
#define __SPHERICAL__

//Spherical lens

#include "Camera.h"
#include "Vector3D.h"
#include "Point2D.h"

class Spherical:public Camera
{
public:

	Spherical();	

	virtual ~Spherical();

	virtual void render_scene(const World &world);

	void set_horizontal_fov(float fov);

	void set_vertical_fov(float fov);

	Vector3D ray_direction(const Point2D& pp,const int hres,const int vres, const float s)const;

private:
	float psi_max;   // vertical view  -90 ！！ 90
	float lambda_max; // horizontal view -180-！！180
};

#endif