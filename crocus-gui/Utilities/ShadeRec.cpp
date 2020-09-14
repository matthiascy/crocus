#include "ShadeRec.h"
#include "World.h"


ShadeRec::ShadeRec(World& _w)
:w(_w),hit_an_object(false),depth(0),u(0),v(0),local_hit_point()
{}

ShadeRec::ShadeRec(const ShadeRec& sr)
:hit_an_object(sr.hit_an_object),
material_ptr(sr.material_ptr),
hit_point(sr.hit_point),
normal(sr.normal),
ray(sr.ray),
w(sr.w),
depth(sr.depth),
t(sr.t),
local_hit_point(sr.local_hit_point),
u(sr.u),
v(sr.v)
{}

ShadeRec::~ShadeRec(void)
{}
