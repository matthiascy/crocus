#include "ViewPlane.h"
#include "Jittered.h"
#include "MultiJittered.h"
#include "Regular.h"


ViewPlane::ViewPlane()
:s(1.0),num_samples(1),max_depth(0)
{
	sampler_ptr = NULL;
}

ViewPlane::~ViewPlane()
{}

void ViewPlane::set_hres(int h_res)
{
	hres = h_res;
}

void ViewPlane::set_vres(int v_res)
{
	vres = v_res;
}

void ViewPlane::set_pixel_size(float size)
{
	s = size;
}

void ViewPlane::set_samples(const int n)
{
	num_samples = n;

	if(sampler_ptr)
	{
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	if(num_samples > 1)
		sampler_ptr = new MultiJittered(n);
	else
		sampler_ptr = new Regular(1);
}

void ViewPlane::set_max_depth(const int n)
{
	max_depth = n;
}

void ViewPlane::set_sampler(Sampler* sp)
{
	if(sampler_ptr)
	{
		delete sampler_ptr;
		sampler_ptr = NULL;
	}

	num_samples = sp->get_num_samples();
	sampler_ptr = sp;
}