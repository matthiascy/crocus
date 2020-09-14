#include "SV_Emissive.h"

SV_Emissive::SV_Emissive()
:ls(1.0),ce(NULL)
{}

SV_Emissive::~SV_Emissive()
{}

RGBColor SV_Emissive::area_light_shade(ShadeRec &sr) const
{
	if( -sr.normal * sr.ray.d > 0.0)
		return (ls * ce->get_color(sr));
	else
		return RGBColor();
}

RGBColor SV_Emissive::shade(ShadeRec &sr) const
{
	if( -sr.normal * sr.ray.d > 0.0)
		return (ls * ce->get_color(sr));
	else
		return RGBColor();
}

void SV_Emissive::set_ce(Texture* tex)
{
	ce = tex;
}

void SV_Emissive::scale_radiance(const float _ls)
{
	ls = _ls;
}

RGBColor SV_Emissive::get_Le(const ShadeRec& sr)const
{
	return (ls * ce->get_color(sr) );
}

RGBColor SV_Emissive::path_shade(ShadeRec& sr)const
{
	if( -sr.normal * sr.ray.d > 0.0)
		return (ls * ce->get_color(sr));
	else
		return RGBColor();
}


RGBColor SV_Emissive::global_shade(ShadeRec& sr)const
{
	if(sr.depth == 1)
		return RGBColor();
	
	if( -sr.normal * sr.ray.d > 0.0)
		return (ls * ce->get_color(sr));
	else
		return RGBColor();
}