#include "Triangle.h"
#include <cmath>
#include "Maths.h"

const double Triangle::kEpsilon = 0.001;

Triangle::Triangle()
:GeometryObject(),v0(0,0,0),v1(0,0,1),v2(1,0,0)
{}

Triangle::Triangle(const Point3D &a, const Point3D &b, const Point3D &c)
:GeometryObject(),v0(a),v1(b),v2(c)
{
	normal = (v1-v0) ^ (v2 - v0);
	normal.normalize();
}


Triangle::~Triangle()
{}


Normal Triangle::get_normal()
{
	return normal;
}

bool Triangle::hit(const Ray &ray, double &tmin, ShadeRec &sr) const
{
	double a = v0.x - v1.x, b = v0.x -v2.x, c = ray.d.x, d = v0.x - ray.o.x;
	double e = v0.y - v1.y, f = v0.y -v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z -v2.z, k = ray.d.z, l = v0.z - ray.o.z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k ,s = e * j - f * i;

	double inv_denom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;

	if(beta < 0.0)
		return false;

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;

	if(gamma < 0.0)
	{
		return false;
	}

	if(beta + gamma > 1.0)
		return false;

	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;

	if(t < kEpsilon)
		return false;

	tmin = t;
	sr.normal = normal;
	sr.local_hit_point = ray.o + t * ray.d;

	return true;
}

bool Triangle::shadow_hit(const Ray &ray, float &tmin) const
{
	double a = v0.x - v1.x, b = v0.x -v2.x, c = ray.d.x, d = v0.x - ray.o.x;
	double e = v0.y - v1.y, f = v0.y -v2.y, g = ray.d.y, h = v0.y - ray.o.y;
	double i = v0.z - v1.z, j = v0.z -v2.z, k = ray.d.z, l = v0.z - ray.o.z;

	double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
	double q = g * i - e * k ,s = e * j - f * i;

	double inv_denom = 1.0 / (a * m + b * q + c * s);

	double e1 = d * m - b * n - c * p;
	double beta = e1 * inv_denom;

	if(beta < 0.0)
		return false;

	double r = e * l - h * i;
	double e2 = a * n + d * q + c * r;
	double gamma = e2 * inv_denom;

	if(gamma < 0.0)
	{
		return false;
	}

	if(beta + gamma > 1.0)
		return false;

	double e3 = a * p - b * r + d * s;
	double t = e3 * inv_denom;

	if(t < kEpsilon)
		return false;

	tmin = t;

	return true;
}

BBox Triangle::get_bounding_box()const
{
	double x0 = min(v0.x,min(v1.x,v2.x));
	double y0 = min(v0.y,min(v1.y,v2.y));
	double z0 = min(v0.z,min(v1.z,v2.z));

	double x1 = max(v0.x,max(v1.x,v2.x));
	double y1 = max(v0.y,max(v1.y,v2.y));
	double z1 = max(v0.z,max(v1.z,v2.z));

	return BBox(x0,y0,z0,x1,y1,z1);
}