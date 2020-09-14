#ifndef __INSTANCE__
#define __INSTANCE__

#include "GeometryObject.h"
#include "Matrix.h"

class Instance:public GeometryObject
{
public:

	Instance(void);

	Instance(GeometryObject* obj_ptr);

	~Instance(void);

	void translate(const float dx, const float dy, const float dz);

	void rotate_x(const float angle);

	void rotate_y(const float angle);

	void rotate_z(const float angle);

	void scale(const float a, const float b, const float c);

	void scale(const float s);

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray,float& tmin)const;

	virtual BBox get_bounding_box()const;

	void compute_bounding_box();

	void reflect_across_x_axis();

	void reflect_across_y_axis();

	void reflect_across_z_axis();

	void transform_texture(const bool trans);

	void shear(const float xy, const float xz, const float yx, const float yz, const float zx, const float zy);

private:

	GeometryObject*		object_ptr;
	Matrix				inv_matrix;

	BBox				bbox;
	static 	Matrix		forward_matrix;
	bool transform_the_texture;
};

inline void Instance::scale(const float s) 
{
	scale(s,s,s);
}

inline void Instance::transform_texture(const bool trans) 
{
	transform_the_texture = trans;
}

#endif