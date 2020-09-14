#ifndef __SOLID_CYLINDER__
#define __SOLID_CYLINDER__

#include "Compound.h"

class SolidCylinder : public Compound
{
public:

	SolidCylinder();

	SolidCylinder(const float bottom, const float top, const float radius);

	~SolidCylinder();

};
#endif