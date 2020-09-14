#ifndef __ROSETTE__
#define __ROSETTE__

// This file contains the declaration of the class Rosette
// This is a rosette configuration of BeveledWedge objects centered on the y axis
// The parameters are:
//				number of rings
//				central hole radius
//				ring width
//				y axis extent
//				bevel radius

// The numbers of wedges in the rings are stored in an array because they 
// must divide 360 exactly

// there is no mortar between the wedges 

// the wedges are stored in a regular grid			

#include "Grid.h"

class Rosette: public Grid 
{
public:

	Rosette(void);   							

	Rosette(	const int 		_num_rings, 
		const double	_hole_radius,
		const double 	_ring_width,
		const double 	_rb,
		const double 	_y0,
		const double 	_y1);	

	Rosette(const Rosette& bb); 				

	virtual Rosette* clone(void) const;

	Rosette& operator= (const Rosette& rhs);		

	virtual ~Rosette(void);

	void construct_rosette(void); 

private:

	double		num_rings;		// maximum of 6
	double		hole_radius;
	double		ring_width;
	double		rb;				// bevel radius
	double		y0, y1;			// y axis extents

	static const int num_wedges[6];  // number of wedges in each ring
};

#endif
