#ifndef __IMAGE__
#define __IMAGE__

#include <vector>		
#include "RGBColor.h"

using namespace std;

class Image 
{	
	public:
	
		Image(void);								

		Image(const Image& image);					

		Image& operator= (const Image& image);		

		~Image(void) ;								
		
		void										
		read_ppm_file(const char* file_name);
		
		int
		get_hres(void);	
		
		int
		get_vres(void);	
				
		RGBColor									
		get_color(const int row, const int col) const;		
		
	private:

		int 				hres;			// horizontal resolution of image
		int					vres;			// vertical resolution of image
		vector<RGBColor> 	pixels;
};

inline int Image::get_hres(void) 
{
	return (hres);
}

inline int Image::get_vres(void) 
{
	return (vres);
}

#endif
		
