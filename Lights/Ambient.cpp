#include "Ambient.h"


Ambient::Ambient()
:Light()
{}

Ambient::~Ambient()
{}


Vector3D Ambient::get_direction(const ShadeRec &sr)
{
	return Vector3D();
}

RGBColor Ambient::L(const ShadeRec &sr)
{
	return (ls * color);
}

bool Ambient::in_shadow(const Ray &ray, const ShadeRec &sr) const
{
	return false;
}