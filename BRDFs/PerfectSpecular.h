#ifndef __PERFECT_SPECULAR__
#define __PERFECT_SPECULAR__

#include "BRDF.h"
#include "Normal.h"

class PerfectSpecular: public BRDF 
{
	public:
	
		PerfectSpecular(void);
		
		~PerfectSpecular(void);
		
		virtual PerfectSpecular* clone(void) const;
		
		void set_kr(const float k);
		
		void set_cr(const RGBColor& c);
		
		void set_cr(const float r, const float g, const float b);
		
		void set_cr(const float c);
		
		virtual RGBColor f(const ShadeRec& sr,const Vector3D& wo,const Vector3D& wi)const;

		virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo,Vector3D& wi)const;
		
		virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wi, float& pdf) const;
		
		virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo) const;
				
	private:
	
		float		kr;			// reflection coefficient
		RGBColor 	cr;			// the reflection color
};


inline void PerfectSpecular::set_kr(const float k) 
{
	kr = k;
}

inline void PerfectSpecular::set_cr(const RGBColor& c) 
{
	cr = c;
}

inline void	PerfectSpecular::set_cr(const float r, const float g, const float b) 
{
	cr.r = r; cr.g = g; cr.b = b;
}

inline void	PerfectSpecular::set_cr(const float c)
{
	cr.r = c; cr.g = c; cr.b = c;
}

#endif