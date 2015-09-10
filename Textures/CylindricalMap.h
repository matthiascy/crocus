#ifndef __CYLINDRICAL_MAP__
#define __CYLINDRICAL_MAP__

#include "Mapping.h"

class CylindricalMap:public Mapping
{
	public:
	
		CylindricalMap(void);									
		
		CylindricalMap(const CylindricalMap& sm);					

		CylindricalMap& operator= (const CylindricalMap& rhs);		

		virtual CylindricalMap*	clone(void) const;				

		~CylindricalMap(void);									
		
		virtual void get_texel_coordinates(const 	Point3D& 	local_hit_point, 
								const 	int 		xres, 
								const 	int 		yres, 
										int& 		row, 
										int& 		column) const;

};

#endif