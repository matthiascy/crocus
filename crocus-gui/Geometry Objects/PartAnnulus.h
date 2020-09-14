#ifndef __PART_ANNULUS__
#define __PART_ANNULUS__

#include "GeometryObject.h"


class PartAnnulus: public GeometryObject 
{

public:

	PartAnnulus(void);

	PartAnnulus(const double y, const double i_r, const double o_r,
		const double azimuth_min,	// in degrees
		const double azimuth_max,	// in degrees
		bool up = true);

	virtual PartAnnulus* clone(void) const;

	PartAnnulus(const PartAnnulus& cp);

	virtual ~PartAnnulus(void);

	PartAnnulus& operator= (const PartAnnulus& rhs);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

	virtual bool shadow_hit(const Ray& ray, float& tmin) const;

public:

	double y;
	double inner_radius;
	double outer_radius;
	double phi_min; // minimum azimiuth angle in degrees measured counter clockwise from the +ve z axis
	double phi_max; // maximum azimiuth angle in degrees measured counter clockwise from the +ve z axis
	double i_r_squared; // stored only to avoid recalculations
	double o_r_squared; // stored only to avoid recalculations
	bool normal_up; // normal is up or down
};

#endif 