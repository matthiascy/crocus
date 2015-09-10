#ifndef __VIEWPLANE__
#define __VIEWPLANE__

class Sampler;

class ViewPlane
{
public:

	ViewPlane();

	~ViewPlane();

	void set_vres(int v_res);

	void set_hres(int h_res);

	void set_pixel_size(float size);

	void set_samples(const int n);

	void set_max_depth(const int n);

	void set_sampler(Sampler* sp);

public:

	int		vres;
	int		hres;
	float	s;
	int		num_samples;
	Sampler*	sampler_ptr;
	int		max_depth;
};

#endif