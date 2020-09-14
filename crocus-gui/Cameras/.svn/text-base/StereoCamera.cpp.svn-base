#include "StereoCamera.h"
#include "Maths.h"
#include "World.h"

StereoCamera::StereoCamera()
:Camera(),viewing(parallel),pixel_gap(1),beta(0.),left_camera_ptr(NULL),right_camera_ptr(NULL)
{}

StereoCamera::~StereoCamera()
{}

void StereoCamera::set_pixel_gap(int g)
{
	pixel_gap = g;
}

void StereoCamera::set_stereo_angle(float a)
{
	beta = a;
}

void StereoCamera::set_left_camera(Camera* c)
{
	left_camera_ptr = c;
}

void StereoCamera::set_right_camera(Camera* c)
{
	right_camera_ptr = c;
}

void StereoCamera::use_parallel_viewing()
{
	viewing = parallel;
}

void StereoCamera::use_transverse_viewing()
{
	viewing = transverse;
}

void StereoCamera::setup_cameras()
{
	double r = eye.distance(lookat);
	double x = r * tan(0.5 * beta * PI_ON_180);

	left_camera_ptr->set_eye(eye - x * u);
	left_camera_ptr->set_lookat(lookat - x * u);
	left_camera_ptr->compute_uvw();

	right_camera_ptr->set_eye(eye + x * u);
	right_camera_ptr->set_lookat(lookat + x * u);
	right_camera_ptr->compute_uvw();

}

void StereoCamera::render_scene(const World& w)
{
	ViewPlane vp = w.vp;
	int hres = vp.hres;
	int vres = vp.vres;

	w.open_window(2 * hres + pixel_gap,vres);

	double r = eye.distance(lookat);
	double x = r * tan(0.5 * beta * PI_ON_180);

	if(viewing == parallel)
	{
		left_camera_ptr->render_stereo(w,x,0);
		right_camera_ptr->render_stereo(w,-x,hres + pixel_gap);
	}
	if(viewing == transverse)
	{
		right_camera_ptr->render_stereo(w,-x,0);
		left_camera_ptr->render_stereo(w,x,hres + pixel_gap);
	}
}