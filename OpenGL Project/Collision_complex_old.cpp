
#include "pch.h"

static float GetAxisOverlap(const glm::vec3& axis, const BoundingBox& boxA, const BoundingBox& boxB) {
	float amin = FLT_MAX;
	float amax = -FLT_MAX;
	float bmin = FLT_MAX;
	float bmax = -FLT_MAX;

	glm::vec3 aminP;
	glm::vec3 amaxP;
	glm::vec3 bminP;
	glm::vec3 bmaxP;

	for (int j = 0; j < boxA.Vertices().size(); ++j) {
		glm::vec3 vertex = boxA.Vertices()[j] + boxA.Position();

		float dotProduct = glm::dot(vertex, axis);

		if (dotProduct < amin) {
			amin = dotProduct;
			aminP = vertex;
		}
		if (dotProduct > amax) {
			amax = dotProduct;
			amaxP = vertex;
		}
	}

	for (int j = 0; j < boxB.Vertices().size(); ++j) {
		glm::vec3 vertex = boxB.Vertices()[j] + boxB.Position();

		float dotProduct = glm::dot(vertex, axis);

		if (dotProduct < bmin) {
			bmin = dotProduct;
			bminP = vertex;
		}
		if (dotProduct > bmax) {
			bmax = dotProduct;
			bmaxP = vertex;
		}
	}

	float overlap = std::min(amax, bmax) - std::max(amin, bmin);

	if (overlap < 0) {
		return 0;
	}
	else {
		return overlap;
	}
}

bool BoundingBox::CollidesWith(const BoundingBox& boxB) {
	int numAxisA = sbb->normals.size();
	int numAxisB = boxB.sbb->normals.size();
	int numAxisCross = numAxisA * numAxisB;
	int totalAxis = numAxisA + numAxisB + numAxisCross;

	for (int i = 0; i < sbb->normals.size(); ++i) {
		glm::vec3 axis = glm::normalize(sbb->normals[i]);

		if (GetAxisOverlap(axis, *this, boxB) == 0) {
			return false;
		}
	}

	for (int i = 0; i < boxB.sbb->normals.size(); ++i) {
		glm::vec3 axis = glm::normalize(boxB.sbb->normals[i]);

		if (GetAxisOverlap(axis, *this, boxB) == 0) {
			return false;
		}
	}

	for (int i = 0; i < sbb->normals.size(); ++i) {
		for (int j = 0; j < boxB.sbb->normals.size(); ++j) {
			glm::vec3 cross = glm::cross(sbb->normals[i], boxB.sbb->normals[j]);

			if (cross == glm::vec3(0, 0, 0)) {
				continue;
			}

			glm::vec3 axis = glm::normalize(cross);

			if (GetAxisOverlap(axis, *this, boxB) == 0) {
				return false;
			}
		}
	}

	return true;
}
