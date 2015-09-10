#include "World.h"
#include "rytracer.h" 
#include "RayCast.h"
#include "Sphere.h"
#include "Pinhole.h"
#include "Normal.h"
#include "RGBColor.h"
#include "Plane.h"
#include "Box.h"
#include "rply.h"
//#include "ply.h"
#include "Triangle.h"
#include "SolidCylinder.h"
#include "Instance.h"
#include "Ambient.h"
#include "PointLight.h"
#include "Directional.h"
#include "Matte.h"
#include "Phong.h"
#include "Emissive.h"
#include "MultiJittered.h"
#include "Jittered.h"
#include "Regular.h"
#include "PureRandom.h"
#include "AmbientOccluder.h"
#include "AreaLighting.h"
#include "Rectangle.h"
#include "AreaLight.h"
#include "EnvironmentLight.h"
#include "Maths.h"
#include "Grid.h"
#include "Reflective.h"
#include "Whitted.h"
#include "GlossyReflector.h"
#include "PathTrace.h"
#include "ConcaveSphere.h"
#include "GlobalTrace.h"
#include "Transparent.h"
#include "Dielectric.h"
#include "GlassOfWater.h"
#include "OpenCylinder.h"
#include "ConvexPartCylinder.h"
#include "Disk.h"
#include "Annulus.h"
#include "FlatRimmedBowl.h"
#include "OpenPartCylinder.h"
#include "Archway.h"
#include "Torus.h"
#include "ThickRing.h"
#include "BeveledBox.h"
#include "ConcavePartCylinder.h"
#include "SolidCone.h"
#include "ConvexPartSphere.h"
#include "ConcavePartSphere.h"
#include "CutFace.h"
#include "BeveledCylinder.h"
#include "BeveledWedge.h"
#include "Rosette.h"
#include "RoundRimmedBowl.h"
#include "FishBowl.h"



#include "Image.h"
#include "SquareMap.h"
#include "SV_Matte.h"
#include "ImageTexture.h"

#include "Checker3D.h"
#include "SphereChecker.h"
#include "CylindricalMap.h"

#include "SV_Emissive.h"
#include "SphericalMap.h"

#include "ConcaveHemisphere.h"
#include "HemisphericalMap.h"

#include "PlaneChecker.h"

#include "FishEye.h"
#include "Spherical.h"
#include "LightProbe.h"
#include "ThinLens.h"
#include "Orthographic.h"
#include "StereoCamera.h"


//#include "fish_bowl.cpp"
//#include "cup.cpp"
//#include "room.cpp"
#include "SSSS.cpp"


World::World()
:tracer_ptr(),camera_ptr(NULL),ambient_ptr(new Ambient),background_color()
{
	
}

World::~World()
{
	if(tracer_ptr)
	{
		delete tracer_ptr;
		tracer_ptr = NULL;
	}
	
		

	if (ambient_ptr) {
		delete ambient_ptr;
		ambient_ptr = NULL;
	}
			
		
	if (camera_ptr)
	{
		delete camera_ptr;
		camera_ptr = NULL;
	}
	
	delete_objects();	
	delete_lights();	
}


void World::delete_objects()
{
	int num_objects = objects.size();

	for(int i = 0;i < num_objects;i++)
	{
		delete objects[i];
		objects[i] = NULL;
	}

	objects.erase(objects.begin(),objects.end());
}

void World::delete_lights()
{
	int num_lights = lights.size();

	for(int i = 0;i < num_lights;i++)
	{
		delete lights[i];
		lights[i] = NULL;
	}

	lights.erase(lights.begin(),lights.end());
}


void World::add_object(GeometryObject *object_ptr)
{
	objects.push_back(object_ptr);
}


void World::open_window(int hres,int vres)const
{
	thread->image = QImage(hres,vres,QImage::Format_ARGB32);
	thread->image.fill(qRgba(0, 0, 0, 0));
}


void World::add_light(Light	*light_ptr)
{
	lights.push_back(light_ptr);
}

void World::set_camera(Camera *c_ptr)
{
	camera_ptr = c_ptr;
}

void World::set_tracer(Tracer *t_ptr)
{
	tracer_ptr = t_ptr;
}




void World::set_ambient_light(Light *light_ptr)
{
	ambient_ptr = light_ptr;
}


RGBColor World::max_to_one(const RGBColor &c)const
{
	float max_value = max(c.r,max(c.g, c.b));

	if(max_value > 1.0)
		return ( c / max_value );
	else
		return c;
}

ShadeRec World::hit_objects(Ray &ray)
{
	ShadeRec	sr((*this));
	double		t;
	Normal		normal;
	int num_objects = objects.size();
	double tmin	= kHugeValue;

	Point3D local_hit_point;



	for(int i=0; i < num_objects; i++)
	{
		if( objects[i]->hit(ray,t,sr) && (t < tmin) )
		{
			//objects[i]->hit(ray,t,sr);
			sr.hit_an_object = true; 
			tmin = t;
			sr.color = objects[i]->color;
			sr.hit_point = ray.o + t * ray.d; 
			sr.material_ptr = objects[i]->get_material();
			normal = sr.normal; 
			local_hit_point = sr.local_hit_point; 
		}
	}
	if(sr.hit_an_object)
	{
		sr.normal = normal;
		sr.t = tmin;
		sr.local_hit_point = local_hit_point;
	}
	return (sr);
}

void World::display_pixel(const int row, const int col, RGBColor L)const
{
	
	L = max_to_one(L);
	thread->setPixel(col,row,255*L.r,255*L.g,255*L.b);
}