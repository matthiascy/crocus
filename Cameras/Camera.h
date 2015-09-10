#ifndef __CAMERA__
#define __CAMERA__

#include "Vector3D.h"
#include "Point3D.h"

class World;
//class Point3D;
//class Vector3D;

class Camera{
public:
	Camera(void);

	virtual ~Camera(void);

	virtual void render_scene(const World& world)=0;

	virtual void render_stereo(const World& w, float x, int offset);

	void set_eye(double _x, double _y, double _z);

	void set_eye(const Point3D& p);

	void set_lookat(double _x, double _y, double _z);

	void set_lookat(const Point3D& p);

	void compute_uvw();

	void set_exposure_time(const float exposure);

	void set_up_vector(const Vector3D& u);

	void set_up_vector(const float x, const float y, const float z);

	void set_roll(const float ra);


protected:


	Point3D		eye;
	Point3D		lookat;
	Vector3D	u,v,w;			// orthonormal basis vectors
	Vector3D	up;
	float		exposure_time;
	float		ra;				// roll angle

};

inline void Camera::set_eye(double _x, double _y, double _z)
{
	eye = Point3D(_x,_y,_z);
}

inline void Camera::set_eye(const Point3D& p)
{
	eye = p;
}

inline void Camera::set_lookat(double _x, double _y, double _z)
{
	lookat = Point3D(_x,_y,_z);
}

inline void Camera::set_lookat(const Point3D& p)
{
	lookat = p;
}

inline void Camera::set_up_vector(const Vector3D& u)
{
	up = u;
}

inline void Camera::set_up_vector(const float x, const float y, const float z) 
{
	up.x = x; up.y = y; up.z = z;
}

inline void Camera::set_roll(const float r) 
{
	ra = r;
}

inline void Camera::set_exposure_time(const float exposure) 
{
	exposure_time = exposure;
}

#endif
