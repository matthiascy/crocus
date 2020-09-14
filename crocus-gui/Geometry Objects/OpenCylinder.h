#ifndef __OPEN_CYLINDER__
#define __OPEN_CYLINDER__

#include "GeometryObject.h"

class OpenCylinder: public GeometryObject
{
	
	public:
		
		OpenCylinder(void);   									

		OpenCylinder(const double bottom, const double top, const double radius);

		OpenCylinder(const OpenCylinder& c); 					
		
		OpenCylinder& operator= (const OpenCylinder& rhs);		
		
		virtual ~OpenCylinder(void);
						
		virtual bool hit(const Ray& ray, double& t, ShadeRec& sr) const;

		virtual bool shadow_hit(const Ray& ray,float& tmin)const;
		
	protected:
	
		double		y0;				// bottom y value
		double		y1;				// top y value
		double		radius;			// radius
		double		inv_radius;  	// one over the radius
		static const double kEpsilon;
};

#endif