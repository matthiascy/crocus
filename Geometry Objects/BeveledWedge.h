#ifndef __BEVELED_WEDGE__
#define __BEVELED_WEDGE__


#include "Compound.h"


class BeveledWedge: public Compound
{

public:
	BeveledWedge(const double y0,		// minimum y value
		const double y1,				// minimum y value
		const double r0,				// inner radius
		const double r1,				// outer radius
		const double rb,				// bevel radius
		const double phi0,				// minimum azimuth angle in degrees
		const double phi1);				// maximum azimuth angle

	BeveledWedge(const BeveledWedge& bw);

	virtual BeveledWedge* clone(void) const;

	virtual BeveledWedge& operator=(const BeveledWedge& rhs);

	virtual ~BeveledWedge(void);

	virtual BBox get_bounding_box(void) const;

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

	virtual bool shadow_hit(const Ray& ray, float& tmin) const;

private:

	double y0;			// minimum y value
	double y1;			// minimum y value
	double r0;			// inner radius
	double r1;			// outer radius
	double rb;			// bevel radius
	double phi0;		// maximum azimuth angle
	double phi1;		// minimum azimuth angle
	BBox bbox;			// bounding box
};

#endif