#ifndef __COMPOUND__
#define __COMPOUND__

#include "GeometryObject.h"
#include <vector>


using namespace std;


class Compound : public GeometryObject
{
public:

	Compound();

	virtual ~Compound();

	void add_object(GeometryObject* object_ptr);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray,float& tmin)const;


private:

	void delete_objects();

protected:

	vector<GeometryObject*> objects;
};

#endif