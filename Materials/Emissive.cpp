#include "Emissive.h"

Emissive::Emissive()
:ls(1.0),ce(1,1,1)
{}

Emissive::~Emissive()
{}

RGBColor Emissive::area_light_shade(ShadeRec &sr) const
{
	if( -sr.normal * sr.ray.d > 0.0)
		return (ls * ce);
	else
		return RGBColor();
}

RGBColor Emissive::shade(ShadeRec &sr) const
{
	if( -sr.normal * sr.ray.d > 0.0)
		return (ls * ce);
	else
		return RGBColor();
}

void Emissive::set_ce(const float r, const float g, const float b)
{
	ce = RGBColor(r,g,b);
}

void Emissive::set_ce( const RGBColor& c )
{
	ce = c;
}

void Emissive::scale_radiance(const float _ls)
{
	ls = _ls;
}

RGBColor Emissive::get_Le(const ShadeRec& sr)const
{
	return (ls * ce );
}

RGBColor Emissive::path_shade(ShadeRec& sr)const
{
	if( -sr.normal * sr.ray.d > 0.0)
		return (ls * ce);
	else
		return RGBColor();
}


RGBColor Emissive::global_shade(ShadeRec& sr)const
{
	if(sr.depth == 1)
		return RGBColor();
	
	if( -sr.normal * sr.ray.d > 0.0)
		return (ls * ce);
	else
		return RGBColor();
}