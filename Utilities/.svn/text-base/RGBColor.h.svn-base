#pragma once


class RGBColor{
public:
	RGBColor();
	RGBColor(float _r,float _g,float _b);
	RGBColor(float a);
	RGBColor(const RGBColor& c);
	~RGBColor();

	RGBColor powc(double d)const;

	RGBColor& operator +=(const RGBColor& c);

	RGBColor& operator /=(const double a);

	RGBColor operator +(const RGBColor& c)const;

	RGBColor operator *(const float a)const;

	RGBColor operator *(const RGBColor& c)const;

	RGBColor operator /(const float a)const;


public:
	float r,g,b;

};

inline RGBColor& RGBColor::operator +=(const RGBColor&	c)
{
	r += c.r;
	g += c.g;
	b += c.b;

	return (*this);
}

inline RGBColor& RGBColor::operator /=(const double a)
{
	r /= a;
	g /= a;
	b /= a;
	return (*this);
}


inline RGBColor RGBColor::operator +(const RGBColor& c)const
{
	return RGBColor(r+c.r,g+c.g,b+c.b);
}

inline RGBColor RGBColor::operator *(const float a)const
{
	return RGBColor(a*r,a*g,a*b);
}

inline RGBColor RGBColor::operator *(const RGBColor& c)const
{
	return RGBColor(r*c.r,g*c.g,b*c.b);
}

inline RGBColor RGBColor::operator /(const float a) const
{
	return RGBColor(r/a,g/a,b/a);
}



//non-member inline function
RGBColor operator* (const float a,const RGBColor& c);

inline RGBColor operator* (const float a,const RGBColor& c)
{
	return RGBColor(a*c.r,a*c.g,a*c.b);
}

