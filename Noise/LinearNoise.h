#ifndef __LINEAR_NOISE__
#define __LINEAR_NOISE__


#include "LatticeNoise.h"


class LinearNoise: public LatticeNoise
{		
public: 

	LinearNoise(void);								

	LinearNoise(int octaves, float lacunarity, float gain);

	LinearNoise(const LinearNoise& lns);		

	virtual LinearNoise* clone(void) const;		

	LinearNoise& operator= (const LinearNoise& rhs);

	virtual ~LinearNoise(void);								

	virtual float value_noise(const Point3D& p) const;

	virtual Vector3D vector_noise(const Point3D& p) const;			
};

template<class T> 
T lerp(const float f, const T& a, const T& b) 
{
	return (a + f * (b - a));
}

#endif
