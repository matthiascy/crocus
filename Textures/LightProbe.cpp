#include "LightProbe.h"

LightProbe::LightProbe(void) 
:Mapping(),map_type(light_probe)
{}

LightProbe::LightProbe(const LightProbe& sm) 
:Mapping(),map_type(sm.map_type)
{}

LightProbe& LightProbe::operator= (const LightProbe& rhs) 
{
	if (this == &rhs)
		return (*this);

	return (*this);
}

LightProbe::~LightProbe (void) {} 

LightProbe*	LightProbe::clone(void) const 
{
	return (new LightProbe(*this));
}	

void LightProbe::get_texel_coordinates(	const 	Point3D& 	local_hit_point, 
										const 	int 		hres, 
										const 	int 		vres, 
												int& 		row, 
												int& 		column) const 
{
	
	float x = local_hit_point.x; 
	float y = local_hit_point.y; 
	float z = local_hit_point.z;
	
	float d = sqrt(x * x + y * y);
	float sin_beta = y / d;
	float cos_beta = x / d;       
	float alpha;
	
	if (map_type == light_probe)   // the default
		alpha = acos(z);
		
	if (map_type == panoramic)
		alpha = acos(-z);
	
	float r = alpha * invPI;     		
	float u = (1.0 + r * cos_beta) * 0.5;
	float v = (1.0 + r * sin_beta) * 0.5;	
	column 	= (int) ((hres - 1) * u);	
	row 	= (int) ((vres - 1) * v);	
}


void LightProbe::set_map_type(Map_type type)
{
	map_type = type;
}