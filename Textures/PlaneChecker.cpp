#include "PlaneChecker.h"
#include "Constants.h"
#include "Maths.h"

PlaneChecker::PlaneChecker()
:size(1.0),outline_width(1.0),color1(black),color2(white),outline_color(red)
{}

PlaneChecker::~PlaneChecker()
{}


void PlaneChecker::set_size(float s)
{
	size = s;
}

void PlaneChecker::set_outline_width(float s)
{
	outline_width = s;
}

void PlaneChecker::set_color1(const RGBColor &c)
{
	color1 = c;
}

void PlaneChecker::set_color2(const RGBColor &c)
{
	color2 = c;
}

void PlaneChecker::set_outline_color(const RGBColor &c)
{
	outline_color = c;
}

RGBColor PlaneChecker::get_color(const ShadeRec &sr) const
{
	float x = sr.local_hit_point.x;
	float y = sr.local_hit_point.y;
	float z = sr.local_hit_point.z;

	int ix = floor( x / size );
	int iz = floor( z / size );
	float fx = x / size - ix;
	float fz = z / size - iz;
	float width = 0.5 * outline_width / size;

	bool in_outline = ( fx < width || fx > 1.0 - width) || ( fz < width || fz > 1.0 -width);

	if( (ix + iz) % 2 ==0 )
	{
		if( !in_outline)
			return color1;
	}
	else
	{
		if( !in_outline )
			return color2;
	}

	return outline_color;

}