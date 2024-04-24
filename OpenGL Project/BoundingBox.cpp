#include "pch.h"

#include "BoundingBox.h"

#ifdef _DEBUG
#include "DebugShader.h"
#endif // _DEBUG

Face::Face(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 n) : vertices{ v1, v2, v3 }, normal(n) {}

//Generates a cube shaped BoundingBox
BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max) :
	center(((max + min) * 0.5f)),
	orientation(glm::vec3(0,0,1))
{
	glm::vec3 vertices[8] = {
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

	glm::vec3 normals[6] = {
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

		faces.emplace_back(vertices[indexes[index1]], vertices[indexes[index2]], vertices[indexes[index3]], normals[i]);
		faces.emplace_back(vertices[indexes[index1]], vertices[indexes[index3]], vertices[indexes[index4]], normals[i]);
	}

	position = glm::vec3(0);
}

glm::vec3 BoundingBox::Center() const {
	return position + center;
}

glm::vec3 BoundingBox::Position() const {
	return position;
}

void BoundingBox::SetPosition(glm::vec3 value) {
	position = value;

	shader->SetPosition(Position());
}

void BoundingBox::SetOrientation(glm::vec3 value) {
	orientation = value;
}

void BoundingBox::Move(glm::vec3 delta) {
	position += delta;

	shader->SetPosition(Position());
}

bool BoundingBox::CollidesWith(const BoundingBox& boxB) {
	std::vector<glm::vec3> axis;

	for (int i = 0; i < faces.size(); ++i) {
		axis.push_back(glm::normalize(faces[i].normal));
	}

	for (int i = 0; i < boxB.faces.size(); ++i) {
		axis.push_back(glm::normalize(boxB.faces[i].normal));
	}

	for (int i = 0; i < faces.size(); ++i) {
		for (int j = 0; j < boxB.faces.size(); ++j) {
			glm::vec3 cross = glm::cross(faces[i].normal, boxB.faces[j].normal);

			if (cross == glm::vec3(0, 0, 0)) {
				//std::cout << "continuing" << std::endl;
				continue;
			}

			axis.push_back(glm::normalize(cross));
		}
	}

	//std::cout << glm::to_string(axis[24]) << std::endl;

	for (int i = 0; i < axis.size(); ++i) {
		float amin = FLT_MAX;
		float amax = -FLT_MAX;
		float bmin = FLT_MAX;
		float bmax = -FLT_MAX;

		glm::vec3 aminP;
		glm::vec3 amaxP;
		glm::vec3 bminP;
		glm::vec3 bmaxP;

		for (int j = 0; j < faces.size(); ++j) {
			for (int k = 0; k < 3; ++k) {
				glm::vec3 vertex = faces[j].vertices[k] + Position();

				//std::cout << "vertexA " << (j * 3 + k) << ": " << glm::to_string(vertex) << std::endl;

				float dotProduct = glm::dot(vertex, axis[i]);

				if (dotProduct < amin) {
					amin = dotProduct;
					aminP = vertex;
				}
				if (dotProduct > amax) {
					amax = dotProduct;
					amaxP = vertex;
				}
			}
		}

		for (int j = 0; j < boxB.faces.size(); ++j) {
			for (int k = 0; k < 3; ++k) {

				glm::vec3 vertex = boxB.faces[j].vertices[k] + boxB.Position();

				//std::cout << "vertexB " << (j * 3 + k) << ": " << glm::to_string(vertex) << std::endl;

				float dotProduct = glm::dot(vertex, axis[i]);

				if (dotProduct < bmin) {
					bmin = dotProduct;
					bminP = vertex;
				}
				if (dotProduct > bmax) {
					bmax = dotProduct;
					bmaxP = vertex;
				}
			}
		}

		bool hasOverlap = (amin < bmax && amin > bmin) || (bmin < amax && bmin > amin);

		if (i == 0 && false) {
			std::cout << "---------------------------------------------------------" << std::endl;
			std::cout << "axis: " << glm::to_string(axis[i]) << std::endl;
			std::cout << "position1: " << glm::to_string(position) << std::endl;
			std::cout << "position2: " << glm::to_string(boxB.position) << std::endl;
			std::cout << "overlap: " << (hasOverlap ? "true" : "false") << std::endl;
			std::cout << "amin: " << amin << "     " << glm::to_string(aminP) << std::endl;
			std::cout << "amax: " << amax << "     " << glm::to_string(amaxP) << std::endl;
			std::cout << "bmin: " << bmin << "     " << glm::to_string(bminP) << std::endl;
			std::cout << "bmax: " << bmax << "     " << glm::to_string(bmaxP) << std::endl;
		}
		

		if (!hasOverlap) {
			return false;
		}
	}

	return true;
}

#ifdef _DEBUG

void BoundingBox::BindGL(Camera* bCam){
	shader = (ShaderProgram*)new DebugShader(bCam, Position());

	for (int i = 0; i < faces.size(); ++i) {
		renderVertices.insert(renderVertices.end(), { faces[i].vertices[0], faces[i].vertices[1], faces[i].vertices[0], faces[i].vertices[2], faces[i].vertices[1], faces[i].vertices[2] });
	}

	GLuint mBuffer;

	glGenVertexArrays(1, &VertexBuffer);
	glBindVertexArray(VertexBuffer);

	glGenBuffers(1, &mBuffer);

	size_t Vertex_Size = sizeof(renderVertices[0]);

	glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
	glBufferData(GL_ARRAY_BUFFER, Vertex_Size * renderVertices.size(), &renderVertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex_Size, 0);
	glEnableVertexAttribArray(0);
	
	glBindVertexArray(0);
}

void BoundingBox::Render() {
	shader->SetPosition(Position());

	shader->Use();

	shader->Update();

	glBindVertexArray(VertexBuffer);

	glDrawArrays(GL_LINES, 0, renderVertices.size() * 3);

	glBindVertexArray(0);
}

#endif // _DEBUG