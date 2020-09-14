#include "Normal.h"
#include "Vector3D.h"
#include <cmath>

Normal::Normal()
{
	x=y=z=0.;
}

Normal::Normal(double _x, double _y, double _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Normal::Normal(const Normal& n)
{
	x = n.x;
	y = n.y;
	z = n.z;
}

Normal::Normal(const Vector3D &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Normal::~Normal()
{

}


double Normal::operator *(const Vector3D &v) const
{
	return ( x * v.x + y * v.y + z * v.z);
}

void Normal::normalize()
{
	double len = sqrt(x*x+y*y+z*z);

	x /= len;
	y /= len;
	z /= len;
}


Normal operator* (const Matrix& mat, const Normal& n) 
{
	return (Normal(	mat.m[0][0] * n.x + mat.m[1][0] * n.y + mat.m[2][0] * n.z,
					mat.m[0][1] * n.x + mat.m[1][1] * n.y + mat.m[2][1] * n.z,
					mat.m[0][2] * n.x + mat.m[1][2] * n.y + mat.m[2][2] * n.z));
}