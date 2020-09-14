#include "HemisphericalMap.h"

HemisphericalMap::HemisphericalMap(void) {}

HemisphericalMap::HemisphericalMap(const HemisphericalMap& sm) {}

HemisphericalMap& HemisphericalMap::operator= (const HemisphericalMap& rhs) 
{
	if (this == &rhs)
		return (*this);

	return (*this);
}

HemisphericalMap::~HemisphericalMap (void) {} 

HemisphericalMap* HemisphericalMap::clone(void) const
{
	return (new HemisphericalMap(*this));
}	

void HemisphericalMap::get_texel_coordinates(	const 	Point3D& 	local_hit_point, 
												const 	int 		xres, 
												const 	int 		yres, 
												int& 		row, 
												int& 		column) const 
{
	
	// first, compute theta and phi
	
	float theta = acos(local_hit_point.y);
	float phi   = atan2(local_hit_point.x, local_hit_point.z);
	if (phi < 0.0)
		phi += TWO_PI;
	
	// next, map theta and phi to (u, v) in [0, 1] X [0, 1]
		
	float u = phi * invTWO_PI;    
	float v = 1.0 - 2.0 * theta * invPI;           
			
	// finally, map u and v to the texel coordinates
		
	column 	= (int) ((xres - 1) * u);   	// column is across
	row 	= (int)  ((yres - 1) * v);    	// row is up
}
