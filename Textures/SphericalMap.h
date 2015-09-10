#ifndef __SPHERICAL_MAP__
#define __SPHERICAL_MAP__


#include "Constants.h"
#include "Mapping.h"

class SphericalMap: public Mapping
{		
	public:
	
		SphericalMap(void);									
		
		SphericalMap(const SphericalMap& sm);					

		SphericalMap& operator= (const SphericalMap& rhs);		

		virtual SphericalMap* clone(void) const;				

		~SphericalMap(void);									
		
		virtual void get_texel_coordinates(	const 	Point3D& 	local_hit_point, 
											const 	int 		xres, 
											const 	int 		yres, 
											int& 		row, 
											int& 		column) const;
};

#endif
		
