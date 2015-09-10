#include "Vector3D.h"
#include "Point3D.h"
#include "Normal.h"
#include <math.h>

Vector3D::Vector3D()
:x(0.),y(0.),z(0.)
{
}

Vector3D::Vector3D(double _x, double _y, double _z)
:x(_x),y(_y),z(_z)
{
}

Vector3D::Vector3D(const Vector3D &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vector3D::Vector3D(const Point3D &p)
{
	x = p.x;
	y = p.y;
	z = p.z;
}

Vector3D::Vector3D(const Normal &n)
{
	x = n.x;
	y = n.y;
	z = n.z;
}

Vector3D::~Vector3D()
{}

void Vector3D::normalize()
{
	double len = sqrt(x*x+y*y+z*z);
	x /= len;
	y /= len;
	z /= len;
}

Vector3D& Vector3D::operator =(const Point3D p)
{
	x = p.x;
	y = p.y;
	z = p.z;
	
	return (*this);
}

Vector3D Vector3D::operator^(const Vector3D &rhs) const
{
	return (Vector3D(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z, x * rhs.y - y * rhs.x));
}

Vector3D& Vector3D::hat()
{
	double len = sqrt(x*x+y*y+z*z);
	x /= len;
	y /= len;
	z /= len;

	return (*this);
}

double Vector3D::length()const
{
	return sqrt(x*x+y*y+z*z);
}

double Vector3D::len_squared()const
{
	return (x*x+ y*y + z*z);
}


Vector3D operator* (const Matrix& mat, const Vector3D& v) 
{
	return (Point3D(mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z,
					mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z,
					mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z));
}
