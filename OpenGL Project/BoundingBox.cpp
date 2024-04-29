#include "pch.h"

#include "BoundingBox.h"

#ifdef _DEBUG
#include "DebugShader.h"
#endif // _DEBUG

//Generates a cube shaped BoundingBox
BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max) :
	center(((max + min) * 0.5f)),
	orientation(glm::vec3(0,0,-1))
{
	vertices = {
		glm::vec3(max),
		glm::vec3(min.x, max.y, max.z),
		glm::vec3(max.x, min.y, max.z),
		glm::vec3(min.x, min.y, max.z),
		glm::vec3(min),
		glm::vec3(max.x, min.y, min.z),
		glm::vec3(min.x, max.y, min.z),
		glm::vec3(max.x, max.y, min.z),
	};

	unsigned int indexes[24] = {
		0, 1, 3, 2,
		4, 5, 7, 6,

		0, 1, 6, 7,
		2, 3, 4, 5,

		0, 2, 5, 7,
		1, 3, 4, 6
	};

	normals = {
		glm::vec3(0,0,1),
		glm::vec3(0,0,-1),
		glm::vec3(0,1,0),
		glm::vec3(0,1,0),
		glm::vec3(1,0,0),
		glm::vec3(-1,0,0),
	};

	for (int i = 0; i < 6; i++) {
		int index1 = i * 4;
		int index2 = index1 + 1;
		int index3 = index1 + 2;
		int index4 = index1 + 3;
		
		indices.insert(indices.end(), {
			indexes[index1], indexes[index2], indexes[index3],
			indexes[index1], indexes[index3], indexes[index4]
		});
	}

	position = glm::vec3(0);
}

const glm::vec3& BoundingBox::Center() const {
	return position + center;
}

const glm::vec3& BoundingBox::Position() const {
	return position;
}

const Orientation& BoundingBox::GetOrientation() const {
	return orientation;
}

void BoundingBox::SetPosition(const glm::vec3& value) {
	position = value;

	if (shader != nullptr) {
		shader->SetPosition(Position());
	}
}

void BoundingBox::SetOrientation(const Orientation& o) {
	orientation = o;
}

void BoundingBox::MoveRelative(const glm::vec3& delta) {
	AxisVectors directions = GetOrientation().GetAxis();

	glm::vec3 rotatedDelta = 
		(glm::vec3(delta.x) * glm::normalize(glm::vec3(directions.Front.x, 0, directions.Front.z))) +
		(glm::vec3(delta.z) * glm::normalize(glm::vec3(directions.Right.x, 0, directions.Right.z)));

	rotatedDelta.y = 0;
	
	position += rotatedDelta;

	if (shader != nullptr) {
		shader->SetPosition(Position());
	}
}

void BoundingBox::MoveAbsolute(const glm::vec3& delta) {
	position += delta;

	if (shader != nullptr) {
		shader->SetPosition(Position());
	}
}

glm::vec3 BoundingBox::ConvertAbsolute(glm::vec3 value) const {
	AxisVectors directions = GetOrientation().GetAxis();

	return 
		(glm::vec3(value.x) * directions.Front) +
		(glm::vec3(value.y) * directions.Up) +
		(glm::vec3(value.z) * directions.Right);
}

bool BoundingBox::CollidesWith(const BoundingBox& boxB) {
	int numAxisA = normals.size();
	int numAxisB = boxB.normals.size();
	int numAxisCross = numAxisA * numAxisB;
	int totalAxis = numAxisA + numAxisB + numAxisCross;

	for (int i = 0; i < normals.size(); ++i) {
		glm::vec3 axis = glm::normalize(normals[i]);
		
		if (GetAxisOverlap(axis, boxB) == 0) {
			return false;
		}
	}

	for (int i = 0; i < boxB.normals.size(); ++i) {
		glm::vec3 axis = glm::normalize(boxB.normals[i]);

		if (GetAxisOverlap(axis, boxB) == 0) {
			return false;
		}
	}

	for (int i = 0; i < normals.size(); ++i) {
		for (int j = 0; j < boxB.normals.size(); ++j) {
			glm::vec3 cross = glm::cross(normals[i], boxB.normals[j]);

			if (cross == glm::vec3(0, 0, 0)) {
				continue;
			}

			glm::vec3 axis = glm::normalize(cross);

			if (GetAxisOverlap(axis, boxB) == 0) {
				return false;
			}
		}
	}

	return true;
}

CollisionInfo BoundingBox::CollidesWith(const BoundingBox& boxB, const glm::vec3& velocity) {
	int numAxisA = normals.size();
	int numAxisB = boxB.normals.size();
	int numAxisCross = numAxisA * numAxisB;
	int totalAxis = numAxisA + numAxisB + numAxisCross;

	//axis, overlap
	std::vector<glm::vec3> axisWithOverlap;
	std::vector<float> adjustedOverlapAmounts;

	for (int i = 0; i < normals.size(); ++i) {
		glm::vec3 axis = glm::normalize(normals[i]);

		float overlap = GetAxisOverlap(axis, boxB);

		if (overlap == 0) {
			return CollisionInfo{ false, 0, glm::vec3(0) };
		}
		else {
			axisWithOverlap.push_back(axis);
			adjustedOverlapAmounts.push_back(glm::dot(axis, velocity));
		}
	}

	for (int i = 0; i < boxB.normals.size(); ++i) {
		glm::vec3 axis = glm::normalize(boxB.normals[i]);

		float overlap = GetAxisOverlap(axis, boxB);

		if (overlap == 0) {
			return CollisionInfo{ false, 0, glm::vec3(0) };
		}
		else {
			axisWithOverlap.push_back(axis);
			adjustedOverlapAmounts.push_back(glm::dot(axis, velocity));
		}
	}

	for (int i = 0; i < normals.size(); ++i) {
		for (int j = 0; j < boxB.normals.size(); ++j) {
			glm::vec3 cross = glm::cross(normals[i], boxB.normals[j]);

			if (cross == glm::vec3(0, 0, 0)) {
				continue;
			}

			glm::vec3 axis = glm::normalize(cross);

			float overlap = GetAxisOverlap(axis, boxB);

			if (overlap == 0) {
				return CollisionInfo{ false, 0, glm::vec3(0) };
			}
			else {
				axisWithOverlap.push_back(axis);
				adjustedOverlapAmounts.push_back(glm::dot(axis, velocity));
			}
		}
	}

	//If the code has gotten to here it means a collision did happen.
	int maxOverlapIndex = -1;

	for (int i = 0; i < adjustedOverlapAmounts.size(); ++i) {

		if (maxOverlapIndex == -1 || adjustedOverlapAmounts[maxOverlapIndex] < adjustedOverlapAmounts[i]) {
			maxOverlapIndex = i;
		}
	}


	return CollisionInfo{true, adjustedOverlapAmounts[maxOverlapIndex], axisWithOverlap[maxOverlapIndex]};
}

float BoundingBox::GetAxisOverlap(const glm::vec3& axis, const BoundingBox& boxB) {
	float amin = FLT_MAX;
	float amax = -FLT_MAX;
	float bmin = FLT_MAX;
	float bmax = -FLT_MAX;

	glm::vec3 aminP;
	glm::vec3 amaxP;
	glm::vec3 bminP;
	glm::vec3 bmaxP;

	for (int j = 0; j < vertices.size(); ++j) {
		glm::vec3 vertex = vertices[j] + Position();

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

	for (int j = 0; j < boxB.vertices.size(); ++j) {
		glm::vec3 vertex = boxB.vertices[j] + boxB.Position();

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

	/*std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << "axis: " << glm::to_string(axis) << std::endl;
	std::cout << "position1: " << glm::to_string(position) << std::endl;
	std::cout << "position2: " << glm::to_string(boxB.position) << std::endl;
	std::cout << "overlap: " << overlap << std::endl;
	std::cout << "amin: " << amin << "     " << glm::to_string(aminP) << std::endl;
	std::cout << "amax: " << amax << "     " << glm::to_string(amaxP) << std::endl;
	std::cout << "bmin: " << bmin << "     " << glm::to_string(bminP) << std::endl;
	std::cout << "bmax: " << bmax << "     " << glm::to_string(bmaxP) << std::endl;*/

	
	if (overlap < 0) {
		return 0;
	}
	else {
		return overlap;
	}
}

#ifdef _DEBUG

void BoundingBox::BindGL(Camera* bCam){
	shader = (ShaderProgram*)new DebugShader(bCam, Position());


	std::vector<unsigned int> renderIndices;

	for (int i = 0; i < indices.size(); i += 3) {

		renderIndices.insert(renderIndices.end(), {
			indices[i],
			indices[i + 1],
			indices[i],
			indices[i + 2],
			indices[i + 1],
			indices[i + 2]
		});
	}

	GLuint mBuffers[2];

	glGenVertexArrays(1, &VertexBuffer);
	glBindVertexArray(VertexBuffer);

	glGenBuffers(2, mBuffers);

	size_t Vertex_Size = sizeof(vertices[0]);

	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, Vertex_Size * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex_Size, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(renderIndices[0]) * renderIndices.size(), &renderIndices[0], GL_STATIC_DRAW);
	
	numIndices = renderIndices.size();

	glBindVertexArray(0);
}

void BoundingBox::Render() {
	shader->SetPosition(Position());

	shader->Use();

	shader->Update();

	glBindVertexArray(VertexBuffer);

	glDrawElements(GL_LINES, numIndices, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

#endif // _DEBUG