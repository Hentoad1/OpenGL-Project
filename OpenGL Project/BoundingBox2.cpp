
#include "pch.h"
#include "BoundingBox2.h"

bool BoundingBox3D::BoxesCollide(const BoundingBox3D& boxA, const BoundingBox3D& boxB) {
	std::vector<glm::vec3> perpendicularLines;


	/*
	https://gamedev.stackexchange.com/questions/44500/how-many-and-which-axes-to-use-for-3d-obb-collision-with-sat
	*/
	
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
				+ boxA.vertices[j].z * perpendicularLines[i].z;

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
				+ boxB.vertices[j].z * perpendicularLines[i].z;

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

BoundingBox3D BoundingBox3D::GenerateFromSize() {
	return BoundingBox3D();
}