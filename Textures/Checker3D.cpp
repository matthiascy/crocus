#include "Checker3D.h"
#include "Constants.h"
#include "Maths.h"

Checker3D::Checker3D()
:size(1.0),color1(black),color2(white)
{}

Checker3D::~Checker3D()
{}


void Checker3D::set_size(float s)
{
	size = s;
}

void Checker3D::set_color1(const RGBColor &c)
{
	color1 = c;
}

void Checker3D::set_color1( const int r, const int g, const int b )
{
	color1.r = r;
	color1.g = g;
	color1.b = b;
}

void Checker3D::set_color2(const RGBColor &c)
{
	color2 = c;
}

void Checker3D::set_color2( const int r, const int g, const int b )
{
	color2.r = r;
	color2.b = b;
	color2.g = g;
}


RGBColor Checker3D::get_color(const ShadeRec &sr) const
{
	float eps = -0.000187453738;
	float x = sr.local_hit_point.x + eps;
	float y = sr.local_hit_point.y + eps;
	float z = sr.local_hit_point.z + eps;

	if( ( (int)floor(x / size) + (int)floor( y / size) + (int)floor(z / size) ) % 2 ==0 )
		return color1;
	else
		return color2;
}