#ifndef __PINHOLE__
#define __PINHOLE__

#include "Camera.h"

class Vector3D;
class Point2D;

class Pinhole:public Camera
{
public:
	Pinhole(void);
	virtual ~Pinhole(void);

	virtual void render_scene(const World& world);

	virtual void render_stereo(const World& w, float x, int offset);

	void set_view_distance(float _d);

	void set_zoom(float z);

	Vector3D get_direction(const Point2D& pp);

private:
	float	d;
	float	zoom;
};

inline void Pinhole::set_view_distance(float _d)
{
	d = _d;
}

inline void Pinhole::set_zoom(float z)
{
	zoom = z;
}

#endif