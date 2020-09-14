#ifndef __CONVEXPART_SPHERE__
#define __CONVEXPART_SPHERE__

#include "GeometryObject.h"


class ConvexPartSphere: public GeometryObject 
{        
public:

	Point3D         center;                         // center coordinates
	double          radius;                         // sphere radius
	double          phi_min;                        // minimum azimiuth angle in degrees measured counter clockwise from the +ve z axis
	double          phi_max;                        // maximum azimiuth angle in degrees measured counter clockwise from the +ve z axis
	double          theta_min;                      // minimum polar angle in degrees measured down from the +ve y axis
	double          theta_max;                      // maximum polar angle in degrees measured down from the +ve y axis

	double          cos_theta_min;          // stored to avoid repeated calculations
	double          cos_theta_max;          // stored to avoid repeated calculations

public:

	ConvexPartSphere(void);                                                                            

	ConvexPartSphere(       const Point3D   c,
		const double    r,
		const double    azimuth_min,    // in degrees
		const double    azimuth_max,    // in degrees
		const double    polar_min,              // in degrees measured from top
		const double    polar_max);             // in degrees measured from top

	ConvexPartSphere(const Point3D c, const double radius);

	virtual ConvexPartSphere* clone(void) const;

	ConvexPartSphere(const ConvexPartSphere& cp);                                          

	virtual ~ConvexPartSphere(void);                                                                        

	ConvexPartSphere& operator= (const ConvexPartSphere& rhs);                                                                

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;  
};

#endif
