#ifndef __CONCAVEPART_CYLINDER__
#define __CONCAVEPART_CYLINDER__

#include "GeometryObject.h"

class ConcavePartCylinder: public GeometryObject {


public:

	ConcavePartCylinder(void);

	ConcavePartCylinder(const double bottom, const double top, const double radius,
						const double azimuth_min,	// in degrees
						const double azimuth_max);	// in degrees

	ConcavePartCylinder(const double bottom, const double top, const double r);

	virtual ConcavePartCylinder* clone(void) const;

	ConcavePartCylinder(const ConcavePartCylinder& cp);

	virtual ~ConcavePartCylinder(void);

	ConcavePartCylinder& operator= (const ConcavePartCylinder& rhs);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

	virtual bool shadow_hit(const Ray& ray, float& tmin) const;

public:

	double y0;			// bottom y value
	double y1;			// top y value
	double radius;		// sphere radius
	double phi_min;		// minimum azimiuth angle in degrees measured counter clockwise from the +ve z axis
	double phi_max;		// maximum azimiuth angle in degrees measured counter clockwise from the +ve z axis
	double inv_radius;	// stored only to avoid recalculations
};

#endif 