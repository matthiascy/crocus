#ifndef __FISH_EYE__
#define __FISH_EYE__

#include "Camera.h"
#include "Vector3D.h"
#include "Point2D.h"

class FishEye:public Camera
{
public:

	FishEye();	

	virtual ~FishEye();

	virtual void render_scene(const World &world);

	void set_fov(float fov);

	Vector3D ray_direction(const Point2D& pp,const int hres,const int vres, const float s, float& r_squared)const;

private:
	float psi_max;   //in degrees
};

#endif