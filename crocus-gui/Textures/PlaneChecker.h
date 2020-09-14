#ifndef __PLANE_CHECKER__
#define __PLANE_CHECKER__

#include "Texture.h"

class PlaneChecker: public Texture 
{	
public:
	
		PlaneChecker(void);									
									
		virtual ~PlaneChecker(void) ;								
		
		virtual RGBColor get_color(const ShadeRec& sr) const;

		void set_size(float s);

		void set_outline_width(float s);

		void set_color1(const RGBColor& c);

		void set_color2(const RGBColor& c);

		void set_outline_color(const RGBColor& c);

private:

	float	size;
	float   outline_width;
	RGBColor color1;
	RGBColor color2;
	RGBColor outline_color;

};

#endif


