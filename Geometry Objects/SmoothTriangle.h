#ifndef __SMOOTH_TRIANGLE__
#define __SMOOTH_TRIANGLE__


#include "GeometryObject.h"

class SmoothTriangle: public GeometryObject 
{
	public:
		
		Normal n0, n1, n2;		// normals at each vertex
		
		SmoothTriangle (void);   										
		
		SmoothTriangle (const Point3D& a, const Point3D& b, const Point3D& c);		

		virtual SmoothTriangle* clone(void) const;
	
		SmoothTriangle(const SmoothTriangle& st); 					

		virtual ~SmoothTriangle(void);   									

		SmoothTriangle& operator= (const SmoothTriangle& rhs);
		
		virtual BBox get_bounding_box(void);
		
		virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;		 					 
		
		virtual bool shadow_hit(const Ray& ray, double& tmin) const;

		virtual Normal get_normal();
		
	private:
		
		Point3D v0, v1, v2;	
		
		Normal interpolate_normal(const float beta, const float gamma) const;
};

#endif

