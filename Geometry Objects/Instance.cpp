#include "Instance.h"
#include "Maths.h"
#include "Constants.h"


Matrix Instance::forward_matrix;

Instance::Instance()
:GeometryObject(),inv_matrix(),object_ptr(NULL),bbox(),transform_the_texture(false)
{
	forward_matrix.set_identity();
}

Instance::Instance(GeometryObject *obj_ptr)
:GeometryObject(),inv_matrix(),object_ptr(obj_ptr),bbox()
{
	material_ptr = object_ptr->get_material();
	forward_matrix.set_identity();
}

Instance::~Instance()
{
	if(object_ptr)
	{
		delete object_ptr;
		object_ptr = NULL;
	}
}


BBox Instance::get_bounding_box()const
{
	return bbox;
}

void Instance::compute_bounding_box()
{
	// First get the object's untransformed BBox
	
	BBox object_bbox = object_ptr->get_bounding_box();
	
	
	// Now apply the affine transformations to the box.
	// We must apply the transformations to all 8 vertices of the orginal box
	// and then work out the new minimum and maximum values
	
	// Construct the eight vertices as 3D points:
	
	Point3D v[8];
	
	v[0].x = object_bbox.x0; v[0].y = object_bbox.y0; v[0].z = object_bbox.z0;
	v[1].x = object_bbox.x1; v[1].y = object_bbox.y0; v[1].z = object_bbox.z0;
	v[2].x = object_bbox.x1; v[2].y = object_bbox.y1; v[2].z = object_bbox.z0;
	v[3].x = object_bbox.x0; v[3].y = object_bbox.y1; v[3].z = object_bbox.z0;
	
	v[4].x = object_bbox.x0; v[4].y = object_bbox.y0; v[4].z = object_bbox.z1;
	v[5].x = object_bbox.x1; v[5].y = object_bbox.y0; v[5].z = object_bbox.z1;
	v[6].x = object_bbox.x1; v[6].y = object_bbox.y1; v[6].z = object_bbox.z1;
	v[7].x = object_bbox.x0; v[7].y = object_bbox.y1; v[7].z = object_bbox.z1;
	
	
	// Transform these using the forward matrix

	v[0] = forward_matrix * v[0];
	v[1] = forward_matrix * v[1];
	v[2] = forward_matrix * v[2];
	v[3] = forward_matrix * v[3];
	v[4] = forward_matrix * v[4];
	v[5] = forward_matrix * v[5];
	v[6] = forward_matrix * v[6];
	v[7] = forward_matrix * v[7];

	
	// Since forward_matrix is a static variable, we must now set it to the unit matrix
	// This sets it up correctly for the next instance object
	
	forward_matrix.set_identity();
	
	
	// Compute the minimum values
	
	float x0 = kHugeValue;
	float y0 = kHugeValue;
	float z0 = kHugeValue;
		
	for (int j = 0; j <= 7; j++)  
	{
		if (v[j].x < x0)
			x0 = v[j].x;
	}
		
	for (int j = 0; j <= 7; j++) 
	{
		if (v[j].y < y0)
			y0 = v[j].y;
	}
		
	for (int j = 0; j <= 7; j++)
	{
		if (v[j].z < z0)
			z0 = v[j].z;
	}
	
	// Compute the minimum values
	
	float x1 = -kHugeValue;
	float y1 = -kHugeValue;
	float z1 = -kHugeValue;   
	
	for (int j = 0; j <= 7; j++) 
	{
		if (v[j].x > x1)
			x1 = v[j].x;
	}
		
	for (int j = 0; j <= 7; j++)
	{
		if (v[j].y > y1)
			y1 = v[j].y;
	}
		
	for (int j = 0; j <= 7; j++) 
	{
		if (v[j].z > z1)
			z1 = v[j].z;
	}
	
	// Assign values to the bounding box
	
	bbox.x0 = x0;
	bbox.y0 = y0;
	bbox.z0 = z0;
	bbox.x1 = x1;
	bbox.y1 = y1;
	bbox.z1 = z1;
}


bool Instance::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
	Ray inv_ray(ray);

	inv_ray.o = inv_matrix * inv_ray.o;
	inv_ray.d = inv_matrix * inv_ray.d;

	if(object_ptr->hit(inv_ray,tmin,sr))
	{
		sr.normal = inv_matrix * sr.normal;
		sr.normal.normalize();

		if(object_ptr->get_material())   
			material_ptr = object_ptr->get_material();

		return true;
	}

	return false;

}

bool Instance::shadow_hit(const Ray &ray, float &tmin) const
{
	Ray inv_ray(ray);

	inv_ray.o = inv_matrix * inv_ray.o;
	inv_ray.d = inv_matrix * inv_ray.d;

	if(object_ptr->shadow_hit(inv_ray,tmin))
	{
		return true;
	}

	return false;
}

void Instance::translate(const float dx, const float dy, const float dz)
{
	Matrix  temp,temp1;
	temp.m[0][3] = -dx;
	temp.m[1][3] = -dy;
	temp.m[2][3] = -dz;

	inv_matrix = inv_matrix * temp;

	temp1.m[0][3] = dx;
	temp1.m[1][3] = dy;
	temp1.m[2][3] = dz;

	forward_matrix = temp1 * forward_matrix;
	compute_bounding_box();
}

void Instance::rotate_x(const float angle)
{
	float tangle = angle  * PI / 180.; 
	double sina = sin(tangle), cosa = cos(tangle);
	Matrix temp,temp1;

	temp.m[1][1] = cosa;
	temp.m[2][2] = cosa;
	temp.m[1][2] = sina;
	temp.m[2][1] = -sina;

	inv_matrix = inv_matrix * temp;

	temp1.m[1][1] = cosa;
	temp1.m[2][2] = cosa;
	temp1.m[1][2] = -sina;
	temp1.m[2][1] = sina;

	forward_matrix = temp1 * forward_matrix;
	compute_bounding_box();
}

void Instance::rotate_y(const float angle)
{
	float tangle = angle  * PI / 180.;
	double sina = sin(tangle), cosa = cos(tangle);
	Matrix temp,temp1;

	temp.m[0][0] = cosa;
	temp.m[2][2] = cosa;
	temp.m[0][2] = -sina;
	temp.m[2][0] = sina;

	inv_matrix = inv_matrix * temp;

	temp1.m[0][0] = cosa;
	temp1.m[2][2] = cosa;
	temp1.m[0][2] = sina;
	temp1.m[2][0] = -sina;

	forward_matrix = temp1 * forward_matrix;
	compute_bounding_box();
}

void Instance::rotate_z(const float angle)
{
	float tangle = angle  * PI / 180.;
	double sina = sin(tangle), cosa = cos(tangle);
	Matrix temp,temp1;

	temp.m[0][0] = cosa;
	temp.m[1][1] = cosa;
	temp.m[0][1] = sina;
	temp.m[1][0] = -sina;

	inv_matrix = inv_matrix * temp;

	temp1.m[0][0] = cosa;
	temp1.m[1][1] = cosa;
	temp1.m[0][1] = -sina;
	temp1.m[1][0] = sina;

	forward_matrix = temp1 * forward_matrix;
	compute_bounding_box();
}


void Instance::scale(const float a, const float b, const float c)
{
	Matrix temp,temp1;

	temp.m[0][0] = 1.0 / a;
	temp.m[1][1] = 1.0 / b;
	temp.m[2][2] = 1.0 / c;

	inv_matrix = inv_matrix * temp;

	temp1.m[0][0] = a;
	temp1.m[1][1] = b;
	temp1.m[2][2] = c;

	forward_matrix = temp1 * forward_matrix;
	compute_bounding_box();
}

/*void
Instance::shear(const float xy, const float xz, const float yx, const float yz, const float zx, const float zy) {

	Matrix inv_shear_matrix;  // temp inverse shear matrix
	Matrix shear_matrix;    // temp sheer matrix

	inv_shear_matrix.m[0][0] = 1 - yz * zy;
	inv_shear_matrix.m[0][1] = -yx + yz * zx;
	inv_shear_matrix.m[0][2] = -zx + yx * zy;
	inv_shear_matrix.m[1][0] = -xy + xz * zy;
	inv_shear_matrix.m[1][1] = 1 - xz * zx;
	inv_shear_matrix.m[1][2] = -zy + xy * zx;
	inv_shear_matrix.m[2][0] = -xz + xy * yz;
	inv_shear_matrix.m[2][1] = -yz + xz * yx;
	inv_shear_matrix.m[2][2] = 1 - xy * yx;

	float inv_determinant = 1 / (1 - xy * yx - xz * zx - yz * zy + xy * yz * zx + xz * yx * zy);

	// post multiply
	inv_matrix = inv_matrix * (inv_shear_matrix.scalar_mult(inv_determinant));

	shear_matrix.m[0][1] = yx;
	shear_matrix.m[0][2] = zx;
	shear_matrix.m[1][0] = xy;
	shear_matrix.m[1][2] = zy;
	shear_matrix.m[2][0] = xz;
	shear_matrix.m[2][1] = yz;

	// pre-multiply
	forward_matrix = shear_matrix * forward_matrix;
}
*/
void
Instance::reflect_across_x_axis()
{

	Matrix inv_reflect_matrix;      // temp inverse reflect matrix
	Matrix reflect_matrix;  // temp reflect matrix

	inv_reflect_matrix.m[0][0] = -1;

	// post multiply
	inv_matrix = inv_matrix * inv_reflect_matrix;

	reflect_matrix.m[1][1] = -1;
	reflect_matrix.m[2][2] = -1;

	// pre-multiply
	forward_matrix = reflect_matrix * forward_matrix;
}

void
Instance::reflect_across_y_axis()
{
	Matrix inv_reflect_matrix;      // temp inverse reflect matrix
	Matrix reflect_matrix;  // temp reflect matrix

	inv_reflect_matrix.m[1][1] = -1;

	// post multiply
	inv_matrix = inv_matrix * inv_reflect_matrix;

	reflect_matrix.m[0][0] = -1;
	reflect_matrix.m[2][2] = -1;

	// pre-multiply
	forward_matrix = reflect_matrix * forward_matrix;
}

void
Instance::reflect_across_z_axis()
{
	Matrix inv_reflect_matrix;      // temp inverse reflect matrix
	Matrix reflect_matrix;  // temp reflect matrix

	inv_reflect_matrix.m[2][2] = -1;

	// post multiply
	inv_matrix = inv_matrix * inv_reflect_matrix;

	reflect_matrix.m[0][0] = -1;
	reflect_matrix.m[1][1] = -1;

	// pre-multiply
	forward_matrix = reflect_matrix * forward_matrix;
}


