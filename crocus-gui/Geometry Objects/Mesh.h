#ifndef __MESH__
#define __MESH__

#include <vector>
#include "Point3D.h"
#include "Normal.h"

using namespace std;


class Mesh
{
public:

	vector<Point3D> vertices;
	vector<int> indices;
	vector<Normal> normals;
	vector<vector<int>> vertex_faces;
	vector<float> u;
	vector<float> v;
	int num_vertices;
	int num_triangles;

	Mesh()
	{
		num_vertices = 0;
		num_triangles = 0;
	};

	~Mesh(){};
};

#endif