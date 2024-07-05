#include "pch.h"

#include "ConvexHull.h"

#define CONVHULL_3D_USE_SINGLE_PRECISION
#define CONVHULL_3D_ENABLE
#include "convhull_3d.h"

#include "qhull/QuickHull.hpp"

BoundingBox CreateConvexHull(const std::vector<Vertex>& mesh_vertices) {
	int* faceIndices = nullptr;
	int nFaces;

	std::vector<glm::vec3> positions;
	positions.reserve(mesh_vertices.size());

	std::vector<quickhull::Vector3<float>> vertices;
	vertices.reserve(mesh_vertices.size());

	for (int i = 0; i < mesh_vertices.size(); ++i) {
		positions.push_back(mesh_vertices[i].GetPosition());
		
		quickhull::Vector3<float> v;
		v.x = mesh_vertices[i].position_x;
		v.y = mesh_vertices[i].position_y;
		v.z = mesh_vertices[i].position_z;

		vertices.push_back(v);
	}

	//convhull_3d_build(&vertices[0], vertices.size(), &faceIndices, &nFaces);
	
	quickhull::QuickHull<float> qh;
	auto hull = qh.getConvexHull(vertices, true, true);
	std::vector<size_t> indices_size_t = hull.getIndexBuffer();
	
	std::vector<unsigned int> indices;
	indices.reserve(indices_size_t.size());

	std::copy(indices_size_t.begin(), indices_size_t.end(), back_inserter(indices));



	/*std::vector<unsigned int> indices;
	indices.reserve(nFaces * 3);
	
	for (int i = 0; i < nFaces * 3; ++i) {
		indices.push_back(faceIndices[i]);
	}*/
	
	
	std::vector<glm::vec3> face_normals;
	face_normals.reserve(indices.size() / 3);

	for (int i = 0; i < indices.size() / 3; ++i) {
		
		const Vertex& a = mesh_vertices[indices[i * 3 + 0]];
		const Vertex& b = mesh_vertices[indices[i * 3 + 1]];
		const Vertex& c = mesh_vertices[indices[i * 3 + 2]];

		glm::vec3 p0 = a.GetPosition() - b.GetPosition();
		glm::vec3 p1 = c.GetPosition() - b.GetPosition();
		glm::vec3 face_n = glm::cross(p0, p1);
		
		float dot = glm::dot(face_n, a.GetNormal());
		
		if (dot < 0.0f) {
			face_normals.push_back(-face_n);
		}
		else {
			face_normals.push_back(face_n);
		}

	}

	ch_free(faceIndices);

	return BoundingBox(positions, indices, face_normals);
}

