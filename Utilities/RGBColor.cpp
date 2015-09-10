#include "RGBColor.h"
#include "Maths.h"

RGBColor::RGBColor()
:r(0),g(0),b(0)
{}

RGBColor::RGBColor(float _r, float _g, float _b)
:r(_r),g(_g),b(_b)
{}

RGBColor::RGBColor(float a)
:r(a),g(a),b(a)
{
}

RGBColor::RGBColor(const RGBColor &c)
{
	r = c.r;
	g = c.g;
	b = c.b;
}

RGBColor::~RGBColor()
{}

RGBColor RGBColor::powc(double d)const
{
	return RGBColor( pow(r,(float)d),pow(g,(float)d),pow(b,(float)d));
}