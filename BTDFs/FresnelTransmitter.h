#ifndef __FRESENL_TRANSMITTER__
#define __FRESENL_TRANSMITTER__

#include "BTDF.h"

class FresnelTransmitter:public BTDF
{
public:

	FresnelTransmitter();

	~FresnelTransmitter();

	virtual RGBColor f(const ShadeRec& sr,const Vector3D& wt,const Vector3D& wo)const;

	virtual RGBColor sample_f(const ShadeRec& sr,const Vector3D& wo,Vector3D& wt)const;

	virtual RGBColor sample_f(const ShadeRec& sr, const Vector3D& wo, Vector3D& wt, float& pdf) const;

	virtual RGBColor rho(const ShadeRec& sr, const Vector3D& wo)const;

	virtual bool tir(const ShadeRec& sr)const;

	float fresnel(const ShadeRec&	sr)const;

	void set_eta_in(const float e);

	void set_eta_out(const float e);

private:

	float kt;
	float eta_in,eta_out;
};


inline void FresnelTransmitter::set_eta_in(const float e)
{
	eta_in = e;
}

inline void FresnelTransmitter::set_eta_out(const float e)
{
	eta_out = e;
}

#endif