#ifndef __TRANSPARENT__
#define __TRANSPARENT__

#include "Phong.h"
#include "PerfectTransmitter.h"
#include "PerfectSpecular.h"

class Transparent:public Phong
{
public:

	Transparent();

	~Transparent();


	void set_kr(const float k);

	void set_kt(const float k);

	void set_ior(const float i);

	virtual RGBColor shade(ShadeRec& sr)const;

private:

	PerfectSpecular*	reflective_brdf;
	PerfectTransmitter*	specular_btdf;

};

inline void Transparent::set_kr(const float k)
{
	reflective_brdf->set_kr(k);
}

inline void Transparent::set_kt(const float k)
{
	specular_btdf->set_kt(k);
}

inline void Transparent::set_ior(const float i)
{
	specular_btdf->set_ior(i);
}

#endif