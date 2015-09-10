#ifndef __CONVEX_CYLINDER__
#define __CONVEX_CYLINDER__

#include "GeometryObject.h"

class ConvexCylinder: public GeometryObject 
{
	
	public:
		
		ConvexCylinder(void);   									

		ConvexCylinder(const double bottom, const double top, const double radius);

		ConvexCylinder(const ConvexCylinder& c); 					
		
		ConvexCylinder& operator= (const ConvexCylinder& rhs);		
		
		virtual ~ConvexCylinder(void);
						
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

