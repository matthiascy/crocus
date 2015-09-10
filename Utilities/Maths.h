#ifndef __MATHS__
#define __MATHS__

#include <stdlib.h>

#include "Constants.h"
#include "RGBColor.h"
#include <cmath>

double min(double x0, double x1);

double max(double x0, double x1);

int rand_int(void);

float rand_float(void);

void set_rand_seed(const int seed);

float rand_float(int l, float h);		// for multi-jittered sampling
	

int	rand_int(int l, int h);			// for multi-jittered sampling
   

double clamp(const double x, const double min, const double max);

int SolveQuadric(double c[3], double s[2]);

int SolveCubic(double c[4], double s[3]);

int SolveQuartic(double c[5], double s[4]);

double mod(double a, const double b); 

double smooth_pulse(double e0, double e1, double e2, double e3, double x);

double smooth_pulse_train(double e0, double e1, double e2, double e3, double period, double x);

double smooth_step(double a, double b, double x);

RGBColor mix_color(const RGBColor& c0, const RGBColor& c1, const double f);

double mix_double(const double a, const double b, const double f);


inline double min(double x0, double x1) 
{
	return ((x0 < x1) ? x0 : x1);
}


inline double max(double x0, double x1) 
{
	return ((x0 > x1) ? x0 : x1);
}

inline int rand_int(void) 
{
	return(rand());
}

inline float rand_float(void) 
{
	return((float)rand_int() * invRAND_MAX);
}

inline void set_rand_seed(const int seed) 
{
	srand(seed);
}

inline float rand_float(int l, float h) 
{
	return (rand_float() * (h - l) + l);
}

inline int rand_int(int l, int h) 
{
	return ((int) (rand_float(0, h - l + 1) + l));
}

inline double clamp(const double x, const double min, const double max) 
{
	return (x < min ? min : (x > max ? max : x));
}

#endif
