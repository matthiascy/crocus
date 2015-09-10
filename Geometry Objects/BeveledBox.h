#ifndef __BEVELED_BOX__
#define __BEVELED_BOX__


#include "Compound.h"
#include "Point3D.h"
#include "BBox.h"

class BeveledBox: public Compound
{

public:

	BeveledBox(void);

	BeveledBox(const Point3D& min_corner, const Point3D& max_corner, const double bevel_radius);

	BeveledBox(const BeveledBox& bb);

	virtual BeveledBox* clone(void) const;

	virtual BeveledBox& operator= (const BeveledBox& rhs);

	virtual ~BeveledBox(void);

	virtual BBox get_bounding_box(void) const;

	virtual bool shadow_hit(const Ray& ray, float& tmin) const;

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;

private:
	Point3D		p0; // minimum coordinate corner
	Point3D		p1;	// maximum coordinate corner
	double		rb;	// bevel radius
	BBox		bbox; // bounding box
};

#endif