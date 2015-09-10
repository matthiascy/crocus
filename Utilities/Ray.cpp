#include "Ray.h"

Ray::Ray(void)
:o(),d()
{
}

Ray::Ray(const Point3D &_o, const Vector3D &_d)
:o(_o),d(_d)
{}

Ray::~Ray(void)
{
}

