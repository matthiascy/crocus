#include "BeveledCylinder.h"
#include "Disk.h"
#include "OpenCylinder.h"
#include "Torus.h"
#include "Instance.h"

BeveledCylinder::BeveledCylinder(void)
:       Compound() 
{
        float bottom = -1;
        float top = 1;
        float radius = 1;
        float bevel_radius = .25;
       
        bbox = BBox(-1, 1, -1, 1, -1, 1);
       
        objects.push_back(new Disk(Point3D(0,bottom,0), radius - bevel_radius, Normal(0, -1, 0)));
        objects.push_back(new Disk(Point3D(0,top,0), radius - bevel_radius, Normal(0,1,0)));
        objects.push_back(new OpenCylinder(bottom + bevel_radius, top - bevel_radius, radius));
       
        Instance* bottom_bevel_ptr = new Instance(new Torus(radius - bevel_radius, bevel_radius));
        bottom_bevel_ptr->translate(0, bottom + bevel_radius, 0);
        objects.push_back(bottom_bevel_ptr);
       
        Instance* top_bevel_ptr = new Instance(new Torus(radius - bevel_radius, bevel_radius));
        top_bevel_ptr->translate(0, top - bevel_radius, 0);
        objects.push_back(top_bevel_ptr);
}

BeveledCylinder::BeveledCylinder(const float bottom, const float top, const float radius, const float bevel_radius)
:       Compound(),
bbox(Point3D(-radius, bottom, -radius), Point3D(radius, top, radius))
{
       
        objects.push_back(new Disk(Point3D(0,bottom,0), radius - bevel_radius, Normal(0, -1, 0)));
        objects.push_back(new Disk(Point3D(0,top,0), radius - bevel_radius, Normal(0,1,0)));
        objects.push_back(new OpenCylinder(bottom + bevel_radius, top - bevel_radius, radius));
       
        Instance* bottom_bevel_ptr = new Instance(new Torus(radius - bevel_radius, bevel_radius));
        bottom_bevel_ptr->translate(0, bottom + bevel_radius, 0);
        objects.push_back(bottom_bevel_ptr);
       
        Instance* top_bevel_ptr = new Instance(new Torus(radius - bevel_radius, bevel_radius));
        top_bevel_ptr->translate(0, top - bevel_radius, 0);
        objects.push_back(top_bevel_ptr);
       
}

BeveledCylinder::BeveledCylinder(const BeveledCylinder& cc)
:       Compound(cc),
bbox(cc.bbox) {}

BeveledCylinder& BeveledCylinder::operator= (const BeveledCylinder& cc) 
{
        if (this == &cc)
                return (*this);
       
        Compound::operator= (cc);
       
        bbox = cc.bbox;
       
        return (*this);
}

BeveledCylinder* BeveledCylinder::clone(void) const 
{
        return (new BeveledCylinder(*this));
}

bool BeveledCylinder::hit(const Ray& ray, double& tmin, ShadeRec& sr) const 
{
        if (bbox.hit(ray))
                return (Compound::hit(ray, tmin, sr));
        else
                return (false);
}

bool BeveledCylinder::shadow_hit(const Ray& ray, float& tmin) const 
{
        if (bbox.hit(ray))
                return (Compound::shadow_hit(ray, tmin));
        else
                return (false);
}

BBox BeveledCylinder::get_bounding_box(void) const 
{
        return bbox;
}
