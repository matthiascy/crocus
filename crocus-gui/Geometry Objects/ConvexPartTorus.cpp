#include "Maths.h"
#include "ConvexPartTorus.h"
#include "Material.h"
#include <math.h>
#include "BBox.h"


ConvexPartTorus::ConvexPartTorus (void):
GeometryObject(),
a(2.0),
b(0.5),
phi_min(0.0), // in radians
phi_max(TWO_PI), // in radians
theta_min(0.0), // in radians measured from top
theta_max(TWO_PI),	// in radians measured from top
bbox(-a - b, a + b, -b, b, -a - b, a + b)
{}


ConvexPartTorus::ConvexPartTorus (const double i_r,
								  const double o_r,
								  const double azimuth_min, // in degrees
								  const double azimuth_max, // in degrees
								  const double polar_min, // in degrees measured from xz plane
								  const double polar_max):	// in degrees measured from xz plane
GeometryObject(),
a(i_r),
b(o_r),
phi_min(azimuth_min * PI_ON_180),	// in radians
phi_max(azimuth_max * PI_ON_180),	// in radians
theta_min(polar_min * PI_ON_180),	// in radians measured from xz plane
theta_max(polar_max * PI_ON_180),	// in radians measured from xz plane
bbox(-a - b, a + b, -b, b, -a - b, a + b) {

	// Authorize negative value for theta_min, but deal with values € [0, 2Pi]
	if (theta_min < 0)
		theta_min += TWO_PI;
}


ConvexPartTorus* ConvexPartTorus::clone(void) const
{
	return new ConvexPartTorus(*this);
}


ConvexPartTorus::ConvexPartTorus (const ConvexPartTorus& ps):
GeometryObject(ps),
a(ps.a),
b(ps.b),
phi_min(ps.phi_min),
phi_max(ps.phi_max),
theta_min(ps.theta_min),
theta_max(ps.theta_max),
bbox(ps.bbox) 
{}

ConvexPartTorus& ConvexPartTorus::operator= (const ConvexPartTorus& rhs) 
{
	if (this == &rhs)
		return *this;

	GeometryObject::operator=(rhs);

	a = rhs.a;
	b = rhs.b;
	phi_min = rhs.phi_min;
	phi_max = rhs.phi_max;
	theta_min = rhs.theta_min;
	theta_max = rhs.theta_max;
	bbox = rhs.bbox;

	return *this;
}

ConvexPartTorus::~ConvexPartTorus(void) 
{
	delete material_ptr;
}

Normal ConvexPartTorus::compute_normal(const Point3D& p) const 
{
	Normal normal;
	double param_squared = a * a + b * b;

	double x = p.x;
	double y = p.y;
	double z = p.z;
	double sum_squared = x * x + y * y + z * z;

	normal.x = 4.0 * x * (sum_squared - param_squared);
	normal.y = 4.0 * y * (sum_squared - param_squared + 2.0 * a * a);
	normal.z = 4.0 * z * (sum_squared - param_squared);
	normal.normalize(); // points outwards

	return normal;
}


bool ConvexPartTorus::hit(const Ray& ray, double& tmin, ShadeRec& sr) const 
{
	if (!bbox.hit(ray))
		return false;

	double x1 = ray.o.x; double y1 = ray.o.y; double z1 = ray.o.z;
	double d1 = ray.d.x; double d2 = ray.d.y; double d3 = ray.d.z;

	double coeffs[5];	// coefficient array for the quartic equation
	double roots[4];	// solution array for the quartic equation

	// define the coefficients of the quartic equation

	double sum_d_sqrd = d1 * d1 + d2 * d2 + d3 * d3;
	double e	= x1 * x1 + y1 * y1 + z1 * z1 - a * a - b * b;
	double f	= x1 * d1 + y1 * d2 + z1 * d3;
	double four_a_sqrd	= 4.0 * a * a;

	coeffs[0] = e * e - four_a_sqrd * (b * b - y1 * y1); // constant term
	coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
	coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
	coeffs[3] = 4.0 * sum_d_sqrd * f;
	coeffs[4] = sum_d_sqrd * sum_d_sqrd; // coefficient of t^4

	// find roots of the quartic equation
	int num_real_roots = SolveQuartic(coeffs, roots);

	bool intersected = false;
	double t = kHugeValue;

	if (num_real_roots == 0) // ray misses the torus
		return false;

	// find the smallest root greater than kEpsilon, if any
	// the roots array is not sorted
	for (int j = 0; j < num_real_roots; j++)
	{
		if (roots[j] > kEpsilon)
		{
			if (roots[j] < t) 
			{
				Vector3D hit = ray.o + roots[j] * ray.d;

				double phi = atan2(hit.x, hit.z);
				if (phi < 0.0)
					phi += TWO_PI;

				double theta = atan2(hit.y, sqrt(hit.x * hit.x + hit.z * hit.z) - a);
				if (theta < 0.0)
					theta += TWO_PI;

				bool good_theta;
				if (theta_max < theta_min)
				{
					good_theta = ((theta_min <= theta && theta <= 360)
						|| (0 <= theta && theta <= theta_max));
				} 
				else
				{
					good_theta = (theta_min <= theta && theta <= theta_max);
				}
				if (phi_min <= phi && phi <= phi_max && good_theta) 
				{
					intersected = true;
					t = roots[j];
				}
			}
		}
	}

	if(!intersected)
		return false;

	tmin = t;
	sr.local_hit_point = ray.o + t * ray.d;
	sr.normal = compute_normal(sr.local_hit_point);

	return true;
}

bool ConvexPartTorus::shadow_hit(const Ray& ray, float& tmin) const 
{
	if (!shadows)
		return false;

	if (!bbox.hit(ray))
		return false;

	double x1 = ray.o.x; double y1 = ray.o.y; double z1 = ray.o.z;
	double d1 = ray.d.x; double d2 = ray.d.y; double d3 = ray.d.z;

	double coeffs[5];	// coefficient array for the quartic equation
	double roots[4];	// solution array for the quartic equation

	// define the coefficients of the quartic equation

	double sum_d_sqrd = d1 * d1 + d2 * d2 + d3 * d3;
	double e = x1 * x1 + y1 * y1 + z1 * z1 - a * a - b * b;
	double f = x1 * d1 + y1 * d2 + z1 * d3;
	double four_a_sqrd	= 4.0 * a * a;

	coeffs[0] = e * e - four_a_sqrd * (b * b - y1 * y1); // constant term
	coeffs[1] = 4.0 * f * e + 2.0 * four_a_sqrd * y1 * d2;
	coeffs[2] = 2.0 * sum_d_sqrd * e + 4.0 * f * f + four_a_sqrd * d2 * d2;
	coeffs[3] = 4.0 * sum_d_sqrd * f;
	coeffs[4] = sum_d_sqrd * sum_d_sqrd; // coefficient of t^4

	// find roots of the quartic equation
	int num_real_roots = SolveQuartic(coeffs, roots);

	bool intersected = false;
	double t = kHugeValue;

	if (num_real_roots == 0) // ray misses the torus
		return false;

	// find the smallest root greater than kEpsilon, if any
	// the roots array is not sorted
	for (int j = 0; j < num_real_roots; j++) 
	{
		if (roots[j] > kEpsilon) 
		{
			if (roots[j] < t)
			{
				Vector3D hit = ray.o + roots[j] * ray.d;

				double phi = atan2(hit.x, hit.z);
				if (phi < 0.0)
					phi += TWO_PI;

				double theta = atan2(hit.y, sqrt(hit.x * hit.x + hit.z * hit.z) - a);
				if (theta < 0.0)
					theta += TWO_PI;

				bool good_theta;
				if (theta_max < theta_min) 
				{
					good_theta = ((theta_min <= theta && theta <= 360)
						|| (0 <= theta && theta <= theta_max));
				} 
				else 
				{
					good_theta = (theta_min <= theta && theta <= theta_max);
				}
				if (phi_min <= phi && phi <= phi_max && good_theta)
				{
					intersected = true;
					t = roots[j];
				}
			}
		}
	}

	if(!intersected)
		return false;

	tmin = t;
	return true;
}