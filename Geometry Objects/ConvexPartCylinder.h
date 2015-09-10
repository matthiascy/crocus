#ifndef __CONVEXPART_CYLINDER__
#define __CONVEXPART_CYLINDER__

#include "GeometryObject.h"

class ConvexPartCylinder: public GeometryObject 
{
public:
       
        ConvexPartCylinder(void);
       
        ConvexPartCylinder(const double bottom, const double top, const double radius, const double azimuth_min, // degrees
                                           const double azimuth_max);
       
        ConvexPartCylinder(const ConvexPartCylinder& c);
       
        virtual ConvexPartCylinder* clone(void) const;
       
        ConvexPartCylinder& operator= (const ConvexPartCylinder& c);
       
        virtual ~ConvexPartCylinder(void);
       
        virtual bool hit(const Ray& ray, double& t, ShadeRec& sr) const;
       
        virtual bool shadow_hit(const Ray& ray, float& t) const;
       
        virtual BBox get_bounding_box(void) const;
       
protected:
       
        double y0;                              // bottom
        double y1;                              // top
        double radius;                  
        double inv_radius;              // 1 / radius
        double          phi_min;                //
        double          phi_max;                //
};

#endif
