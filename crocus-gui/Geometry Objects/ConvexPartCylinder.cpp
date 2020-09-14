#include "ConvexPartCylinder.h"
#include "Maths.h"
#include "Constants.h"

ConvexPartCylinder::ConvexPartCylinder(void)
:       GeometryObject(),
        y0(-1.0),
        y1(1.0),
        radius(1.0),
        inv_radius(1.0),
        phi_min(0.0),
        phi_max(TWO_PI)
{}

ConvexPartCylinder::ConvexPartCylinder(const double bottom, const double top, const double r,
        const double azimuth_min, // degrees
        const double azimuth_max) // degrees)
:       GeometryObject(),
        y0(bottom),
        y1(top),
        radius(r),
        inv_radius(1.0 / r),
        phi_min(azimuth_min * PI_ON_180),
        phi_max(azimuth_max * PI_ON_180)
{}

ConvexPartCylinder::ConvexPartCylinder(const ConvexPartCylinder& c)
:       GeometryObject(c),
        y0(c.y0),
        y1(c.y1),
        radius(c.radius),
        inv_radius(c.inv_radius),
        phi_max(c.phi_max),
        phi_min(c.phi_min)
{}

ConvexPartCylinder* ConvexPartCylinder::clone(void) const 
{
        return (new ConvexPartCylinder(*this));
}

ConvexPartCylinder& ConvexPartCylinder::operator= (const ConvexPartCylinder& c) 
{
        if (this == &c)
                return (*this);
       
        GeometryObject::operator= (c);
       
        y0 = c.y0;
        y1 = c.y1;
        radius = c.radius;
        inv_radius = c.inv_radius;
        phi_max = c.phi_max;
        phi_min = c.phi_min;
       
        return (*this);
}

ConvexPartCylinder::~ConvexPartCylinder(void) {}

BBox ConvexPartCylinder::get_bounding_box(void) const 
{
        double delta = 0.0001;
       
        return (BBox(Point3D(-radius - delta, y0 - delta, -radius - delta),
                                 Point3D(radius + delta, y1 + delta, radius + delta)));
}

bool ConvexPartCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const 
{
       
        double t;
        double ox = ray.o.x;
        double oy = ray.o.y;
        double oz = ray.o.z;
        double dx = ray.d.x;
        double dy = ray.d.y;
        double dz = ray.d.z;
       
        double a = dx * dx + dz * dz;  
        double b = 2.0 * (ox * dx + oz * dz);                                  
        double c = ox * ox + oz * oz - radius * radius;
        double disc = b * b - 4.0 * a * c ;
       
       
        if (disc < 0.0)
                return(false);
        else {  
                double e = sqrt(disc);
                double denom = 2.0 * a;
                t = (-b - e) / denom;    // smaller root
               
                if (t > kEpsilon) 
				{
                        double yhit = oy + t * dy;
                       
                        if (yhit > y0 && yhit < y1)
						{
                               
                                Vector3D hit = ray.o + t * ray.d;
                               
                                double phi = atan2(hit.x, hit.z);
                                if (phi < 0.0)
                                        phi += TWO_PI;
                               
                                if (phi >= phi_min && phi <= phi_max) 
								{
                               
                                        tmin = t;
                                        sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
                                       
                                        // test for hitting from inside
                                       
                                        if (-ray.d * sr.normal < 0.0)
                                                sr.normal = -sr.normal;
                                       
                                        sr.local_hit_point = ray.o + tmin * ray.d;
                                       
                                        return (true);
                                }
                        }
                }
               
                t = (-b + e) / denom;    // larger root
               
                if (t > kEpsilon)
				{
                        double yhit = oy + t * dy;
                       
                        if (yhit > y0 && yhit < y1)
						{
                               
                                Vector3D hit = ray.o + t * ray.d;
                               
                                double phi = atan2(hit.x, hit.z);
                                if (phi < 0.0)
                                        phi += TWO_PI;
                               
                                if (phi >= phi_min && phi <= phi_max) 
								{
                               
                                        tmin = t;
                                        sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
                                       
                                        // test for hitting inside surface
                                       
                                        if (-ray.d * sr.normal < 0.0)
                                                sr.normal = -sr.normal;
                                       
                                        sr.local_hit_point = ray.o + tmin * ray.d;
                                       
                                        return (true);
                                }
                        }
                }
        }
       
        return (false);                
}



bool ConvexPartCylinder::shadow_hit(const Ray& ray, float& tmin) const 
{
       
        double t;
        double ox = ray.o.x;
        double oy = ray.o.y;
        double oz = ray.o.z;
        double dx = ray.d.x;
        double dy = ray.d.y;
        double dz = ray.d.z;
       
        double a = dx * dx + dz * dz;  
        double b = 2.0 * (ox * dx + oz * dz);                                  
        double c = ox * ox + oz * oz - radius * radius;
        double disc = b * b - 4.0 * a * c ;
       
       
        if (disc < 0.0)
                return(false);
        else
		{  
                double e = sqrt(disc);
                double denom = 2.0 * a;
                t = (-b - e) / denom;    // smaller root
               
                if (t > kEpsilon) 
				{
                        double yhit = oy + t * dy;
                       
                        if (yhit > y0 && yhit < y1) 
						{
                               
                                Vector3D hit = ray.o + t * ray.d;
                               
                                double phi = atan2(hit.x, hit.z);
                                if (phi < 0.0)
                                        phi += TWO_PI;
                               
                                if (phi >= phi_min && phi <= phi_max) 
								{
                                       
                                        tmin = t;
//                                      sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
//                                      
//                                      // test for hitting from inside
//                                      
//                                      if (-ray.d * sr.normal < 0.0)
//                                              sr.normal = -sr.normal;
//                                      
//                                      sr.local_hit_point = ray.o + tmin * ray.d;
                                       
                                        return (true);
                                }
                        }
                }
               
                t = (-b + e) / denom;    // larger root
               
                if (t > kEpsilon) 
				{
                        double yhit = oy + t * dy;
                       
                        if (yhit > y0 && yhit < y1)
						{
                               
                                Vector3D hit = ray.o + t * ray.d;
                               
                                double phi = atan2(hit.x, hit.z);
                                if (phi < 0.0)
                                        phi += TWO_PI;
                               
                                if (phi >= phi_min && phi <= phi_max) 
								{
                                       
                                        tmin = t;
//                                      sr.normal = Normal((ox + t * dx) * inv_radius, 0.0, (oz + t * dz) * inv_radius);
//                                      
//                                      // test for hitting inside surface
//                                      
//                                      if (-ray.d * sr.normal < 0.0)
//                                              sr.normal = -sr.normal;
//                                      
//                                      sr.local_hit_point = ray.o + tmin * ray.d;
                                       
                                        return (true);
                                }
                        }
                }
        }
       
        return (false);                        
}

