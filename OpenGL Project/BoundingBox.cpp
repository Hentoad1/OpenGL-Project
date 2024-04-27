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
	auto& z = GetOrientation();
	
	z.GetAxis();

	AxisVectors directions = GetOrientation().GetAxis();

	glm::vec3 rotatedDelta =
		(glm::vec3(delta.x) * directions.Front) +
		(glm::vec3(delta.z) * directions.Right);

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

bool BoundingBox::CollidesWith(const BoundingBox& boxB) {
	std::vector<glm::vec3> axis;

	int numAxisA = normals.size();
	int numAxisB = boxB.normals.size();
	int numAxisCross = numAxisA * numAxisB;
	int totalAxis = numAxisA + numAxisB + numAxisCross;

	for (int i = 0; i < normals.size(); ++i) {
		glm::vec3 axis = glm::normalize(normals[i]);
		
		if (!AxisCollidesWith(axis, boxB)) {
			return false;
		}
	}

	for (int i = 0; i < boxB.normals.size(); ++i) {
		glm::vec3 axis = glm::normalize(boxB.normals[i]);

		if (!AxisCollidesWith(axis, boxB)) {
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

			if (!AxisCollidesWith(axis, boxB)) {
				return false;
			}
		}
	}

	return true;
}

bool BoundingBox::AxisCollidesWith(const glm::vec3& axis, const BoundingBox& boxB) {
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

	bool hasOverlap = (amin < bmax && amin > bmin) || (bmin < amax && bmin > amin);

	/*
	std::cout << "---------------------------------------------------------" << std::endl;
	std::cout << "axis: " << glm::to_string(axis[i]) << std::endl;
	std::cout << "position1: " << glm::to_string(position) << std::endl;
	std::cout << "position2: " << glm::to_string(boxB.position) << std::endl;
	std::cout << "overlap: " << (hasOverlap ? "true" : "false") << std::endl;
	std::cout << "amin: " << amin << "     " << glm::to_string(aminP) << std::endl;
	std::cout << "amax: " << amax << "     " << glm::to_string(amaxP) << std::endl;
	std::cout << "bmin: " << bmin << "     " << glm::to_string(bminP) << std::endl;
	std::cout << "bmax: " << bmax << "     " << glm::to_string(bmaxP) << std::endl;
	*/


	/*
	if overlap is true, next axis is tested.
	if overlap is false, collision does not exist and processing can be stopped.
	*/
	return hasOverlap;
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