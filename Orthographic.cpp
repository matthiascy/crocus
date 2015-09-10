#include "Orthographic.h"
#include "Vector3D.h"
#include "World.h"

Orthographic::Orthographic(void):
Camera(),
d(lookat.distance(eye)),
dir(lookat - eye) {

	dir.normalize();
}

Orthographic::Orthographic(const Orthographic& o):
Camera(o),
d(o.d),
dir(o.dir) {
}

Camera* Orthographic::clone(void) const 
{
	return new Orthographic(*this);
}

Orthographic& Orthographic::operator=(const Orthographic& rhs) 
{
	if (this == &rhs)
		return *this;

	Camera::operator= (rhs);

	d = rhs.d;
	dir = rhs.dir;

	return *this;
}

Orthographic::~Orthographic(void) {}

void Orthographic::compute_direction(void) 
{
	dir = Vector3D(lookat-eye);
	dir.normalize();
}

void Orthographic::compute_distance(void) 
{
	d = lookat.distance(eye);
}

void Orthographic::render_scene(const World& w) 
{
	RGBColor	L;
	ViewPlane	vp(w.vp);
	Ray	ray;
	int depth = 0;
	Point2D pp;	// sample point on a pixel
	int n = (int)sqrt((float)vp.num_samples);

	compute_direction();
	compute_distance();

	ray.d = dir;

	for (int r = 0; r < vp.vres; r++) // up
		for (int c = 0; c < vp.hres; c++) {	// across
			L = black;

			for (int p = 0; p < n; p++)	// up pixel
				for (int q = 0; q < n; q++) {	// across pixel
					pp.x = vp.s * (c - 0.5 * vp.hres + (q + 0.5) / n);
					pp.y = vp.s * (r - 0.5 * vp.vres + (p + 0.5) / n);
					ray.o = Point3D(pp.x, pp.y, 0);
					L += w.tracer_ptr->trace_ray(ray, depth);
				}

				L /= vp.num_samples;
				//L *= exposure_time;
				w.display_pixel(r, c, L);
		}
}