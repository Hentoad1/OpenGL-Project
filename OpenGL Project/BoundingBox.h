#pragma once

#include "pch.h"

#include "Orientation.h"
#include "EngineInternal.h"

#ifdef _DEBUG
#include "Shader.h"
#include "Camera.h"
#endif // _DEBUG

class BoundingBox {

public:
	BoundingBox() {}

	BoundingBox(
		const std::vector<glm::vec3>& _vertices,
		const std::vector<unsigned int>& _indices,
		const std::vector<glm::vec3>& _normals,
		const glm::vec3& _position,
		const Orientation& _orientation,
		const glm::vec3& _center
	) : vertices(_vertices), indices(_indices), normals(_normals), position(_position), orientation(_orientation), center(_center) {}

	BoundingBox(glm::vec3 min, glm::vec3 max);

	const glm::vec3& Center() const;

	const glm::vec3& Position() const;

	const std::vector<glm::vec3>& Vertices() const;

	const Orientation& GetOrientation() const;

	void MoveRelative(const glm::vec3&);

	void MoveAbsolute(const glm::vec3&);

	void SetPosition(const glm::vec3&);

	void SetOrientation(const Orientation&);

	CollisionInfo CollidesWith(const BoundingBox&, const glm::vec3&);

	bool CollidesWith(const BoundingBox&);

	glm::vec3 ConvertAbsolute(glm::vec3) const;

#ifdef _DEBUG
	void BindGL(Camera*);

	void Render();
#endif // _DEBUG

private:
	//vertices remains static, regardless of orientation or position
	std::vector<glm::vec3> vertices;

	//indices remains static, regardless of orientation or position
	std::vector<unsigned int> indices;

	//normals remains static, regardless of orientation or position
	std::vector<glm::vec3> normals;

	//center remains static, regardless of orientation or position
	glm::vec3 center;

	//position is dynamic, changing possbily every frame.
	glm::vec3 position = glm::vec3(0);

	//orientation is dynamic, changing possibly every frame.
	Orientation orientation;

#ifdef _DEBUG
	unsigned int numIndices;

	ShaderProgram* shader;
	GLuint VertexBuffer;
#endif
};