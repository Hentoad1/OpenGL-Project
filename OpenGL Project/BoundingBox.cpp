#include "pch.h"

#include "BoundingBox.h"

static std::vector<glm::vec3> GetVertices(glm::vec3 max, glm::vec3 min) {
	std::vector<glm::vec3> ;
}


//Generates a cube shaped BoundingBox
BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max) :
	center(((max + min) * 0.5f)),
	vertices({
		glm::vec3(max),
		glm::vec3(min.x, max.y, max.z),
		glm::vec3(max.x, min.y, max.z),
		glm::vec3(max.x, max.y, min.z),
		glm::vec3(max.x, min.y, min.z),
		glm::vec3(min.x, max.y, min.z),
		glm::vec3(min.x, min.y, max.z),
		glm::vec3(min),
	}),
	edges({
		glm::vec3(max.x - min.x, 0, 0),
		glm::vec3(min.x - max.x, 0, 0),
		glm::vec3(0, max.y - min.y, 0),
		glm::vec3(0, min.y - max.y, 0),
		glm::vec3(0, 0, max.z - min.z),
		glm::vec3(0, 0, min.z - max.z),
	}),
	position(glm::vec3(0)),
	orientation(glm::vec3(0,0,1))
	{}

glm::vec3 BoundingBox::Center() const {
	return position + center;
}

glm::vec3 BoundingBox::Position() const {
	return position;
}

void BoundingBox::SetPosition(glm::vec3 value) {
	position = value;
}

void BoundingBox::SetOrientation(glm::vec3 value) {
	orientation = value;
}

void BoundingBox::Move(glm::vec3 delta) {
	position += delta;
}

bool BoundingBox::CollidesWith(const BoundingBox& boxB) {
	std::vector<glm::vec3> perpendicularLines;


	/*
	https://gamedev.stackexchange.com/questions/44500/how-many-and-which-axes-to-use-for-3d-obb-collision-with-sat
	*/

	for (int i = 0; i < edges.size(); ++i) {
		perpendicularLines.emplace_back(glm::cross(orientation, edges[i]));
	}

	for (int i = 0; i < boxB.edges.size(); ++i) {
		perpendicularLines.emplace_back(glm::cross(boxB.orientation, boxB.edges[i]));
	}


	for (int i = 0; i < perpendicularLines.size(); ++i) {
		float amin = FLT_MAX;
		float amax = -FLT_MAX;
		float bmin = FLT_MAX;
		float bmax = -FLT_MAX;


		for (int j = 0; j < vertices.size(); ++j) {

			float dotProduct =
				vertices[j].x * perpendicularLines[i].x
				+ vertices[j].y * perpendicularLines[i].y
				+ vertices[j].z * perpendicularLines[i].z;

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

		bool hasOverlap = (amin < bmax && amin > bmin) || (bmin < amax && bmin > amin);

		std::cout << i << "    " << amax << "    " << amin << "    " << bmax << "    " << bmin << "    " << hasOverlap << std::endl;

		if (hasOverlap) {
			return true;
		}
	}

	return false;
}