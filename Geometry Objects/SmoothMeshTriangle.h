#ifndef __SMOOTH_MESH_TRIANGLE__
#define __SMOOTH_MESH_TRIANGLE__


#include "MeshTriangle.h"

class SmoothMeshTriangle: public MeshTriangle
{		
	public:
		
		SmoothMeshTriangle(void);   									
		
		SmoothMeshTriangle(Mesh* _meshPtr, const int i0, const int i1, const int i2);		

		virtual SmoothMeshTriangle* clone(void) const;
	
		SmoothMeshTriangle(const SmoothMeshTriangle& fmt); 					

		virtual ~SmoothMeshTriangle(void);   									

		SmoothMeshTriangle& operator= (const SmoothMeshTriangle& rhs);
				
		virtual	bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const; 																	

	protected:
	
		Normal interpolate_normal(const float beta, const float gamma) const;
};

#endif

