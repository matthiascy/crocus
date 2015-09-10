#include "ImageTexture.h"

ImageTexture::ImageTexture(void)
	:	Texture(),
		hres(100),
		vres(100),
		image_ptr(NULL),
		mapping_ptr(NULL)
{}

ImageTexture::ImageTexture(Image* _image_ptr)
	:	Texture(),
		hres(_image_ptr->get_hres()),
		vres(_image_ptr->get_vres()),
		image_ptr(_image_ptr),
		mapping_ptr(NULL)
{}

ImageTexture::ImageTexture(const ImageTexture& it)
	: 	Texture(it),
		hres(it.hres),
		vres(it.vres)
{
	if (it.image_ptr)
		*image_ptr = *it.image_ptr;
	else
		image_ptr = NULL;
		
	if (it.mapping_ptr)
		mapping_ptr = it.mapping_ptr->clone();
	else
		mapping_ptr = NULL;
}


ImageTexture& ImageTexture::operator= (const ImageTexture& rhs) 
{
	if (this == &rhs)
		return (*this);
	
	Texture::operator= (rhs);
	
	hres = rhs.hres;
	vres = rhs.vres;
	
	if (image_ptr) 
	{
		delete image_ptr;
		image_ptr = NULL;
	}
	
	if (rhs.image_ptr)
		*image_ptr = *rhs.image_ptr;
	
	if (mapping_ptr)
	{
		delete mapping_ptr;
		mapping_ptr = NULL;
	}
	
	if (rhs.mapping_ptr)
		mapping_ptr = rhs.mapping_ptr->clone();

	return (*this);
}

ImageTexture* ImageTexture::clone(void) const 
{
	return (new ImageTexture (*this));
}	

ImageTexture::~ImageTexture (void) 
{

	if (image_ptr) 
	{
		delete image_ptr;
		image_ptr = NULL;
	}
	
	if (mapping_ptr) 
	{
		delete mapping_ptr;
		mapping_ptr = NULL;
	}
}

RGBColor ImageTexture::get_color(const ShadeRec& sr) const 
{	
	int row;
	int column;
		
	if (mapping_ptr)
		mapping_ptr->get_texel_coordinates(sr.local_hit_point, hres, vres, row, column);
	else
	{
		row 	= (int)(sr.v * (vres - 1));  	
		column 	= (int)(sr.u * (hres - 1));	
	}
	
	return (image_ptr->get_color(row, column));
}  





