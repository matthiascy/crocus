#include "ThinLens.h"
#include "ViewPlane.h"
#include "Ray.h"
#include "World.h"

ThinLens::ThinLens():
Camera(),
lens_radius(1.0),
d(40.0),
f(50.0),
zoom(1.0),
sampler_ptr(NULL) {
}

ThinLens::ThinLens(const ThinLens& tl):
Camera(tl),
lens_radius(tl.lens_radius),
d(tl.d),
f(tl.f),
zoom(tl.zoom),
sampler_ptr(NULL) {
}

ThinLens* ThinLens::clone(void) const 
{
	return new ThinLens(*this);
}

ThinLens::~ThinLens(void)
{
	delete sampler_ptr;
}

void ThinLens::set_sampler(Sampler* sp)
{
	delete sampler_ptr;
	sampler_ptr = sp;
	sampler_ptr->map_samples_to_unit_disk();
}

Vector3D ThinLens::ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const
{
	Point2D p; // hit point on focal plane
	p.x = pixel_point.x * f / d;
	p.y = pixel_point.y * f / d;

	Vector3D dir = (p.x - lens_point.x) * u + (p.y - lens_point.y) * v - f * w;
	dir.normalize();

	return dir;
}

void ThinLens::render_scene(const World& w) 
{
	RGBColor L;
	Ray ray;
	ViewPlane vp(w.vp);
	int depth = 0;

	Point2D sp; // sample point in [0, 1] x [0, 1]
	Point2D pp; // sample point on a pixel
	Point2D dp; // sample point on unit disk
	Point2D lp; // sample point on lens

	vp.s /= zoom;

	for (int r = 0; r < vp.vres - 1; r++) { // up
		for (int c = 0; c < vp.hres - 1; c++) { // across
			L = black;

			for (int n = 0; n < vp.num_samples; n++) {
				sp = vp.sampler_ptr->sample_unit_square();
				pp.x = vp.s * (c - vp.hres / 2.0 + sp.x);
				pp.y = vp.s * (r - vp.vres / 2.0 + sp.y);

				dp = sampler_ptr->sample_unit_disk();
				lp = dp * lens_radius;

				ray.o = eye + lp.x * u + lp.y * v;
				ray.d = ray_direction(pp, lp);
				L += w.tracer_ptr->trace_ray(ray, depth);
			}

			L /= vp.num_samples;
			L = L * exposure_time;
			w.display_pixel(r, c, L);
		}
	}

}