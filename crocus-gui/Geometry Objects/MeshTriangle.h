#ifndef __MESH_TRIANGLE__
#define __MESH_TRIANGLE__


#include "GeometryObject.h"
#include "Mesh.h"

class MeshTriangle: public GeometryObject 
{	
	public:

		Mesh* 		mesh_ptr;					// stores all the data
		int			index0, index1, index2;  	// indices into the vertices array in the mesh
		Normal		normal;					
		float		area;						// required for translucency
	
	public:
		
		MeshTriangle(void);   	  									
		
		MeshTriangle(Mesh* _mesh_ptr, const int i1, const int i2, const int i3);		

		virtual MeshTriangle* clone(void) const = 0;
	
		MeshTriangle(const MeshTriangle& mt); 					

		virtual ~MeshTriangle(void);   									

		MeshTriangle& operator= (const MeshTriangle& rhs);
		
		virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr) const;
		
		virtual	bool shadow_hit(const Ray& ray, float& tmin) const;
		
		void compute_normal(const bool reverse_normal);
				
		virtual Normal get_normal(void);				

		virtual BBox get_bounding_box(void)const;
		
	protected:
	
		float interpolate_u(const float beta, const float gamma) const;
		
		float interpolate_v(const float beta, const float gamma) const;			
};

#endif