#ifndef __JITTERED__
#define __JITTERED__

#include "Sampler.h"

class Jittered:public Sampler
{
public:

	Jittered();

	Jittered(const int num);

	Jittered(const int num,const int nsets);

	~Jittered();


private:

	virtual void generate_samples(void);
};

#endif