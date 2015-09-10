#ifndef __HEMISPHERE_MAP__
#define __HEMISPHERE_MAP__

#include "Constants.h"
#include "Mapping.h"

class HemisphericalMap: public Mapping {		
	public:
	
		HemisphericalMap(void);									
		
		HemisphericalMap(const HemisphericalMap& sm);					

		HemisphericalMap& operator= (const HemisphericalMap& rhs);		

		virtual HemisphericalMap* clone(void) const;				

		~HemisphericalMap(void);									
		
		virtual void get_texel_coordinates(	const 	Point3D& 	local_hit_point, 
											const 	int 		xres, 
											const 	int 		yres, 
											int& 		row, 
											int& 		column) const; 
};

#endif

		
