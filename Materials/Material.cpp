#include "Material.h"

Material::Material()
{}

Material::~Material()
{}

RGBColor Material::get_Le(const ShadeRec& sr)const
{
	return RGBColor();
}

RGBColor Material::area_light_shade(ShadeRec &sr) const
{
	return RGBColor();
}

RGBColor Material::shade(ShadeRec &sr) const
{
	return RGBColor();
}

RGBColor Material::path_shade(ShadeRec &sr) const
{
	return RGBColor();
}

RGBColor Material::global_shade(ShadeRec &sr)const
{
	return RGBColor();
}

void Material::set_sampler(Sampler* s)
{}