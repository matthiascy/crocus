#ifndef __DIELECTRIC__
#define __DIELECTRIC__

#include "Phong.h"
#include "FresnelTransmitter.h"
#include "FresnelReflector.h"

class Dielectric:public Phong
{
public:

	Dielectric();

	~Dielectric();

	void set_eta_in(const float e);

	void set_eta_out(const float e);

	void set_cf_in(const RGBColor& c);

	void set_cf_in(const float r, const float g, const float b);

	void set_cf_out(const RGBColor& c);

	void set_cf_out(const float r, const float g, const float b);

	virtual RGBColor shade(ShadeRec& sr)const;

private:

	RGBColor	cf_in;
	RGBColor	cf_out;

	FresnelReflector*	fresnel_brdf;
	FresnelTransmitter*	fresnel_btdf;

};

inline void Dielectric::set_cf_in(const RGBColor& c)
{
	cf_in = c;
}

inline void Dielectric::set_cf_in( const float r, const float g, const float b )
{
	cf_in.r = r;
	cf_in.g = g;
	cf_in.b = b;
}

inline void Dielectric::set_cf_out(const RGBColor& c)
{
	cf_out = c;
}

inline void Dielectric::set_cf_out(const float r, const float g, const float b)
{
	cf_out.r = r;
	cf_out.g = g;
	cf_out.b = b;
}

inline void Dielectric::set_eta_in(const float e)
{
	fresnel_brdf->set_eta_in(e);
	fresnel_btdf->set_eta_in(e);
}

inline void Dielectric::set_eta_out(const float e)
{
	fresnel_brdf->set_eta_out(e);
	fresnel_btdf->set_eta_out(e);
}

#endif