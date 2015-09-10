#ifndef __CONCAVEPART_SPHERE__
#define __CONCAVEPART_SPHERE__

#include "GeometryObject.h"

class ConcavePartSphere: public GeometryObject 
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

	ConcavePartSphere(void);                                                                            

	ConcavePartSphere(      const Point3D   c,
		const double    r,
		const double    azimuth_min,    // in degrees
		const double    azimuth_max,    // in degrees
		const double    polar_min,              // in degrees measured from top
		const double    polar_max);             // in degrees measured from top

	ConcavePartSphere(const Point3D c, const double radius);

	virtual ConcavePartSphere* clone(void) const;

	ConcavePartSphere(const ConcavePartSphere& cp);                                                

	virtual ~ConcavePartSphere(void);                                                                      

	ConcavePartSphere& operator= (const ConcavePartSphere& rhs);                                                              

	virtual bool hit(const Ray& r, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray,float& tmin)const;
};

#endif

