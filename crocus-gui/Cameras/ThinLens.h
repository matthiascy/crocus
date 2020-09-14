#ifndef __THINLENS__
#define __THINLENS__

#include "Camera.h"
#include "Sampler.h"

class ThinLens: public Camera {
public:

	ThinLens(void);

	ThinLens(const ThinLens& tl);

	virtual ThinLens* clone(void) const;

	ThinLens& operator=(const ThinLens& rhs);

	virtual ~ThinLens(void);

	void set_lens_radius(float lr);

	void set_view_distance(float new_d);

	void set_focal_distance(float new_f);

	void set_zoom(float z);

	void set_sampler(Sampler* sp);

	Vector3D ray_direction(const Point2D& pixel_point, const Point2D& lens_point) const;

	virtual void render_scene(const World& w);

private:

	float lens_radius; // lens radius
	float d; // view plane distance
	float f; // focal plane
	float zoom; // zoom factor
	Sampler* sampler_ptr; // sampler object
};


inline void ThinLens::set_lens_radius(float lr)
{
	lens_radius = lr;
}

inline void ThinLens::set_view_distance(float new_d) 
{
	d = new_d;
}

inline void ThinLens::set_focal_distance(float new_f)
{
	f = new_f;
}

inline void ThinLens::set_zoom(float z) 
{
	zoom = z;
}

#endif