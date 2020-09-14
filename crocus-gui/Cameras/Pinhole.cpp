#include "Pinhole.h"
#include "World.h"
#include "Point2D.h"
#include "Constants.h"
#include "rytracer.h"
#include "Sampler.h"
#include <cmath>

Pinhole::Pinhole(void)
:Camera(),d( 100.),zoom(1.0)
{
}

Pinhole::~Pinhole(void)
{
}

void Pinhole::render_scene(const World& world)
{
	RGBColor L;
	ViewPlane vp(world.vp);
	Ray	ray;
	Point2D pp;
	Point2D sp;

	world.open_window(vp.hres,vp.vres);

	ray.o = eye;
	vp.s /= zoom;

	for(int r = 0; r < vp.vres; r++)
		for(int c = 0; c < vp.hres; c++)
		{
			L = black;

			for(int i = 0;i<vp.num_samples;i++)
				{
					sp = vp.sampler_ptr->sample_unit_square();

					pp.x = vp.s * ( c - vp.hres * 0.5 + sp.x);
					pp.y = vp.s * ( r - vp.vres * 0.5 + sp.y);

					ray.d = get_direction(pp);

					L += world.tracer_ptr->trace_ray(ray,0);

				}
			L /= vp.num_samples;
			world.display_pixel(r,c,L);
		}
}


void Pinhole::render_stereo(const World &world,float x,int offset)
{
	RGBColor L;
	ViewPlane vp(world.vp);
	Ray	ray;
	Point2D pp;
	Point2D sp;

	ray.o = eye;
	vp.s /= zoom;

	for(int r = 0; r < vp.vres; r++)
		for(int c = 0; c < vp.hres; c++)
		{
			L = black;

			for(int i = 0;i<vp.num_samples;i++)
				{
					sp = vp.sampler_ptr->sample_unit_square();

					pp.x = vp.s * ( c - vp.hres * 0.5 + sp.x);
					pp.y = vp.s * ( r - vp.vres * 0.5 + sp.y);

					ray.d = get_direction(pp);

					L += world.tracer_ptr->trace_ray(ray,0);

				}
			L /= vp.num_samples;
			world.display_pixel(r,c + offset,L);
		}
}

Vector3D Pinhole::get_direction(const Point2D &p)
{
	Vector3D dir = p.x * u + p.y * v - d * w;
	dir.normalize();
	
	return(dir);
}
