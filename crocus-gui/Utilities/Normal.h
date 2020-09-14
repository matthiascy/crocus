#ifndef __NORMAL__
#define __NORMAL__

#include "Matrix.h"

class Vector3D;

class Normal
{
public:

	Normal(void);

	Normal(double _x, double _y, double _z);

	Normal(const Normal& n);

	Normal(const Vector3D& v);

	~Normal(void);

	Normal operator-(void)const;

	Normal& operator+=(const Normal& n);

	double operator* (const Vector3D& v) const;

	void normalize();

public:
	double x, y, z;
};


inline Normal Normal::operator- (void) const 
{
	return (Normal(-x, -y, -z));
}

inline Normal& Normal::operator +=(const Normal &n)
{
	x += n.x;
	y += n.y;
	z += n.z;
	return (*this);
}

Normal operator* (const Matrix& mat, const Normal& n);

#endif