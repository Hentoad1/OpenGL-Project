#pragma once

#include "pch.h"

#include "Shader.h"


#ifdef _DEBUG
#include "Camera.h"
#endif // _DEBUG

struct Face {
	Face(glm::vec3, glm::vec3, glm::vec3, glm::vec3);

	glm::vec3 vertices[3];
	glm::vec3 normal;
};

class BoundingBox {

public:
	BoundingBox() {}

	BoundingBox(
		std::vector<Face> _faces,
		glm::vec3 _position,
		glm::vec3 _orientation,
		glm::vec3 _center
	) : faces(_faces), position(_position), orientation(_orientation), center(_center) {}

	BoundingBox(glm::vec3 min, glm::vec3 max);

	glm::vec3 Center() const;

	glm::vec3 Position() const;

	void Move(glm::vec3);

	void SetPosition(glm::vec3);

	void SetOrientation(glm::vec3);

	bool CollidesWith(const BoundingBox&);

#ifdef _DEBUG
	void BindGL(Camera*);

	void Render();
#endif // _DEBUG

private:
	//faces remain static, regardless of orientation or position
	std::vector<Face> faces;

	//normals remain static, regardless of orientation or position
	std::vector<glm::vec3> normals;

	//center remain static, regardless of orientation or position
	glm::vec3 center;

	//position is dynamic, changing possbily every frame.
	glm::vec3 position = glm::vec3(0);

	//orientation is dynamic, chaning possibly every frame.
	glm::vec3 orientation;

#ifdef _DEBUG
	std::vector<glm::vec3> renderVertices;

	ShaderProgram* shader{};
	GLuint VertexBuffer{};
#endif
};