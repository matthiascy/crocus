#ifndef GENERICGenericSphere_H
#define GENERICGenericSphere_H

// This file contains the declaration of the class GenericSphere

#include "GeometryObject.h"
#include "BBox.h"

class GenericSphere: public GeometryObject {

public:
	GenericSphere(void);
	GenericSphere(const GenericSphere& GenericSphere);
	virtual GenericSphere* clone(void) const;
	virtual	~GenericSphere(void);
	GenericSphere& operator= (const GenericSphere& genericSphere);

	BBox get_bounding_box(void) const;

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
	virtual bool shadow_hit(const Ray& ray, float& tmin) const;
};

#endif // GENERICGenericSphere_H