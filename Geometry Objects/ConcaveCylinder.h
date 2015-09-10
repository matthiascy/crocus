#ifndef __CONCAVE_CYLINDER__
#define __CONCAVE_CYLINDER__

#include "GeometryObject.h"

class ConcaveCylinder: public GeometryObject 
{
	
	public:
		
		ConcaveCylinder(void);   									

		ConcaveCylinder(const double bottom, const double top, const double radius);

		ConcaveCylinder(const ConcaveCylinder& c); 					
		
		ConcaveCylinder& operator= (const ConcaveCylinder& rhs);		
		
		virtual ~ConcaveCylinder(void);
						
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

