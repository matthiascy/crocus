#ifndef __GRID__
#define __GRID__

#include "Compound.h"
#include "Mesh.h"

class Grid: public Compound
{
public:

	Grid();

	Grid(Mesh* _mesh_ptr); 

	~Grid();

	virtual BBox get_bounding_box();

	void setup_cells();

	virtual bool hit(const Ray& ray, double& tmin, ShadeRec& sr)const;

	virtual bool shadow_hit(const Ray& ray,float& tmin)const;

	void read_flat_triangles(char* file_name);

	void read_smooth_triangles(char* file_name);

	void read_ply_file(char* file_name, const int triangle_type);

	void compute_mesh_normals(void);


private:
	vector<GeometryObject*>		cells;
	BBox			bbox;
	int			nx,ny,nz;


	Mesh*						mesh_ptr;		// holds triangle data
	bool						reverse_normal;	// some PLY files have normals that point inwards

	Point3D		find_min_bounds();
	Point3D		find_max_bounds();
};

#endif
