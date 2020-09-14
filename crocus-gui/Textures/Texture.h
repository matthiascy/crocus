#ifndef __TEXTURE__
#define __TEXTURE__

#include "RGBColor.h"
#include "ShadeRec.h"

class Texture
{
public:

	Texture();

	virtual ~Texture();

	virtual RGBColor get_color(const ShadeRec& sr)const = 0;
};

#endif