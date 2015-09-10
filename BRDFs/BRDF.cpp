#include "BRDF.h"

BRDF::BRDF()
:sampler_ptr(NULL)
{}

BRDF::~BRDF()
{}

void BRDF::set_sampler(Sampler *sPtr)
{
	if(sampler_ptr)
	{
		delete sampler_ptr;
		sampler_ptr = NULL;
	}
	sampler_ptr = sPtr;
	sampler_ptr->map_samples_to_hemisphere(1.);
}
