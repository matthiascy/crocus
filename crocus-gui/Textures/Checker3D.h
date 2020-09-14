#ifndef __CHECKER__
#define __CHECKER__

#include "Texture.h"

class Checker3D: public Texture 
{	
public:
	
		Checker3D(void);									
									
		virtual ~Checker3D(void);								
		
		virtual RGBColor get_color(const ShadeRec& sr) const;

		void set_size(float s);

		void set_color1(const RGBColor& c);

		void set_color1(const int r, const int g, const int b);

		void set_color2(const RGBColor& c);

		void set_color2(const int r, const int g, const int b);

private:

	float	size;
	RGBColor color1;
	RGBColor color2;

};

#endif


