
#include "pch.h"

#include "BuildAABB.h"

StaticBoundingBox* BuildAABB(const glm::vec3& min, const glm::vec3& max) {

	glm::vec3 center = (max + min) * 0.5f;

	std::vector<glm::vec3> vertices = {
		glm::vec3(max),
		glm::vec3(min.x, max.y, max.z),
		glm::vec3(max.x, min.y, max.z),
		glm::vec3(min.x, min.y, max.z),
		glm::vec3(min),
		glm::vec3(max.x, min.y, min.z),
		glm::vec3(min.x, max.y, min.z),
		glm::vec3(max.x, max.y, min.z),
	};

	std::vector<glm::vec3> normals = {
		glm::vec3(0,0,1),
		glm::vec3(0,0,-1),
		glm::vec3(0,1,0),
		glm::vec3(0,1,0),
		glm::vec3(1,0,0),
		glm::vec3(-1,0,0),
	};

	std::vector<unsigned int> indices;

	unsigned int face_indices[] = {
		0, 1, 3, 2,
		4, 5, 7, 6,

		0, 1, 6, 7,
		2, 3, 4, 5,

		0, 2, 5, 7,
		1, 3, 4, 6
	};

	for (int i = 0; i < 6; i++) {

		int index1 = i * 4;
		int index2 = index1 + 1;
		int index3 = index1 + 2;
		int index4 = index1 + 3;

		indices.insert(indices.end(), {

			//face 1 of square
			face_indices[index1], face_indices[index2],
			face_indices[index2], face_indices[index3],
			face_indices[index1], face_indices[index3],

			//face 2 of square
			face_indices[index1], face_indices[index3],
			face_indices[index1], face_indices[index4],
			face_indices[index3], face_indices[index4],

			});
	}

	return new StaticBoundingBox{ vertices, indices, normals, min, max, center, BoundingBoxType_AABB };
}