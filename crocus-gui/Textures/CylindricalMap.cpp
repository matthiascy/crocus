#include "CylindricalMap.h"
#include "Constants.h"
#include "Maths.h"

CylindricalMap::CylindricalMap(void) {}

CylindricalMap::CylindricalMap(const CylindricalMap& sm) {}

CylindricalMap& CylindricalMap::operator= (const CylindricalMap& rhs) 
{
	if (this == &rhs)
		return (*this);

	return (*this);
}

CylindricalMap::~CylindricalMap (void) {} 

CylindricalMap*	CylindricalMap::clone(void) const 
{
	return (new CylindricalMap(*this));
}	

void CylindricalMap::get_texel_coordinates(	const 	Point3D& 	local_hit_point, 
											const 	int 		xres, 
											const 	int 		yres, 
											int& 		row, 
											int& 		column) const 
{
	
	float phi = atan2(local_hit_point.x,local_hit_point.z);

	if( phi < 0.0 )
		phi += TWO_PI;
		
	
	float u = phi * invTWO_PI;
	float v =  0.5 * (local_hit_point.y + 1.);         
			
	// finally, map u and v to the texel coordinates
		
	column 	= (int) ((xres - 1) * u);   	// column is across
	row 	= (int)  ((yres - 1) * v);    	// row is up
}

