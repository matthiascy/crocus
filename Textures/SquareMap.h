#ifndef __SQUARE_MAP__
#define __SQUARE_MAP__

#include "Constants.h"
#include "Mapping.h"

class SquareMap: public Mapping 
{		
	public:
	
		SquareMap(void);									
		
		SquareMap(const SquareMap& sm);					

		SquareMap& operator= (const SquareMap& rhs);		

		virtual SquareMap* clone(void) const;				

		~SquareMap(void);									
		
		virtual void get_texel_coordinates(	const 	Point3D& 	local_hit_point, 
											const 	int 		xres, 
											const 	int 		yres, 
											int& 		row, 
											int& 		column) const;
};

#endif
