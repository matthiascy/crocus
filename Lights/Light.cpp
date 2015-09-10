#include "Light.h"

Light::Light()
:color(1,1,1),ls(1.0),shadows(true)
{}

Light::~Light()
{}

void Light::set_color(float r,float g, float b)
{
	color = RGBColor(r,g,b);
}

void Light::scale_radiance(const float b)
{
	ls = b;
}

void Light::set_shadows(bool b)
{
	shadows = b;
}

bool Light::casts_shadows()
{
	return shadows;
}

float Light::G(const ShadeRec &sr) const
{
	return 1;
}

float Light::pdf(const ShadeRec &sr) const
{
	return 1;
}

Vector3D Light::get_direction(const ShadeRec& sr)
{
	return Vector3D();
}

RGBColor Light::L(const ShadeRec& sr)
{
	return (ls * color);
}

bool Light::in_shadow(const Ray &ray, const ShadeRec &sr) const
{
	return false;
}