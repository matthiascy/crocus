#ifndef __SAMPLER__
#define __SAMPLER__


#include <vector>
#include <math.h>

#include "Point2D.h"
#include "Point3D.h"
#include "Maths.h"

class Sampler 
{	
public:	

	Sampler(void);								

	Sampler(const int num);						

	Sampler(const int num, const int num_sets);		

	Sampler(const Sampler& s);						

	Sampler& operator= (const Sampler& rhs);				
			
	virtual ~Sampler(void);							

	void set_num_sets(const int np);					

	virtual void generate_samples(void) = 0;


	int get_num_samples(void);							

	void shuffle_x_coordinates(void);

	void shuffle_y_coordinates(void);

	void setup_shuffled_indices(void);

	void map_samples_to_unit_disk(void);

	void map_samples_to_hemisphere(const float p);		

	void map_samples_to_sphere(void);					

	Point2D sample_unit_square(void);							// get next sample on unit square
		
	Point2D	sample_unit_disk(void);								// get next sample on unit disk

	Point3D	sample_hemisphere(void);							// get next sample on unit hemisphere

	Point3D	sample_sphere(void);								// get next sample on unit sphere

	Point2D	sample_one_set(void);								// only used to set up a vector noise table

protected:

	int 					num_samples;     		// the number of sample points in a set
	int 					num_sets;				// the number of sample sets
	std::vector<Point2D>	samples;				// sample points on a unit square
	std::vector<int>		shuffled_indices;		// shuffled samples array indices
	std::vector<Point2D>	disk_samples;			// sample points on a unit disk
	std::vector<Point3D> 	hemisphere_samples;		// sample points on a unit hemisphere
	std::vector<Point3D> 	sphere_samples;			// sample points on a unit sphere
	unsigned long 			count;					// the current number of sample points used
	int 					jump;					// random index jump
};

#endif

