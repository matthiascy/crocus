#include "Mapping.h"

Mapping::Mapping(void) {}

Mapping::Mapping(const Mapping& m) {}
	
Mapping& Mapping::operator= (const Mapping& rhs) 
{
	if (this == &rhs)
		return (*this);

	return (*this);
}

Mapping::~Mapping(void) {} 