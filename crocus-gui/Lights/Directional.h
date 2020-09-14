#ifndef __DIRECTIONAL__
#define __DIRECTIONAL__

#include "Light.h"
#include "Vector3D.h"
#include "RGBColor.h"
#include "ShadeRec.h"


class Directional: public Light {
	public:
	
		Directional(void);   							

		Directional(const Directional& dl); 
		
		Directional& operator= (const Directional& rhs); 
			
		virtual	~Directional(void); 
				
		void set_direction(Vector3D d);						
		
		void set_direction(float dx, float dy, float dz);
		
		virtual Vector3D get_direction(const ShadeRec& sr);
				
		virtual RGBColor L(const ShadeRec& sr);

		virtual bool in_shadow(const Ray& ray,const ShadeRec& sr)const;
		
	private:
		Vector3D	dir;		// direction the light comes from
};


inline void Directional::set_direction(Vector3D d) 
{
	dir = d;
	dir.normalize();
}

inline void Directional::set_direction(float dx, float dy, float dz) 
{
	dir.x = dx; dir.y = dy; dir.z = dz;
	dir.normalize();
}


#endif

