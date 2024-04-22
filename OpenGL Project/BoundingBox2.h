#pragma once

#include "pch.h"




class BoundingBox3D {

public:
	BoundingBox3D() {}

	BoundingBox3D(const std::vector<glm::vec3>& _vertices, const std::vector<glm::vec3>& _edges) : vertices(_vertices), edges(_edges) { }

	std::vector<glm::vec3> edges;
	std::vector<glm::vec3> vertices;
	glm::vec3 orientation = glm::vec3(0, 0, 1);

	//separating axis theorem
	static bool BoxesCollide(const BoundingBox3D& boxA, const BoundingBox3D& boxB);

	static BoundingBox3D GenerateFromSize();
};

/*
FUNCTION WORKS AS LONG AS ORIENTATION IS (0, 0, 1)


bool BoundingBox3D::BoxesCollide(const BoundingBox3D& boxA, const BoundingBox3D& boxB) {
	std::vector<glm::vec2> perpendicularLines;

	for (int i = 0; i < boxA.edges.size(); ++i) {
		perpendicularLines.emplace_back(glm::cross(boxA.orientation, boxA.edges[i]));
	}

	for (int i = 0; i < boxB.edges.size(); ++i) {
		perpendicularLines.emplace_back(glm::cross(boxB.orientation, boxB.edges[i]));
	}

	for (int i = 0; i < perpendicularLines.size(); ++i) {
		float amin = FLT_MAX;
		float amax = -FLT_MAX;
		float bmin = FLT_MAX;
		float bmax = -FLT_MAX;


		for (int j = 0; j < boxA.vertices.size(); ++j) {

			float dotProduct =
				boxA.vertices[j].x * perpendicularLines[i].x
				+ boxA.vertices[j].y * perpendicularLines[i].y
				;// +boxA.vertices[j].z * perpendicularLines[i].z;

			if (dotProduct < amin) {
				amin = dotProduct;
			}
			if (dotProduct > amax) {
				amax = dotProduct;
			}
		}


		for (int j = 0; j < boxB.vertices.size(); ++j) {

			float dotProduct =
				boxB.vertices[j].x * perpendicularLines[i].x
				+ boxB.vertices[j].y * perpendicularLines[i].y
				;// +boxB.vertices[j].z * perpendicularLines[i].z;

			if (dotProduct < bmin) {
				bmin = dotProduct;
			}
			if (dotProduct > bmax) {
				bmax = dotProduct;
			}
		}

		std::cout << i << "    " << amax << "    " << amin << "    " << bmax << "    " << bmin << "    " << ((amin < bmax && amin > bmin) || (bmin < amax && bmin > amin)) << std::endl;

		if (!((amin < bmax && amin > bmin) || (bmin < amax && bmin > amin))) {
			return false;
		}
	}

	return true;
}
*/