#pragma once

#include "pch.h"

#include "Orientation.h"
#include "EngineInternal.h"

#ifdef _DEBUG
#include "Shader.h"
#include "Camera.h"
#endif // _DEBUG

enum BoundingBoxType : uint8_t{
	BoundingBoxType_AABB,
	BoundingBoxType_CONVEX_HULL,
	BoundingBoxType_COMPLEX
};

struct StaticBoundingBox {

	//vertices remains static, regardless of orientation or position
	std::vector<glm::vec3> vertices;

	//indices remains static, regardless of orientation or position
	std::vector<unsigned int> indices;

	//normals remains static, regardless of orientation or position
	std::vector<glm::vec3> normals;

	//min remains static, regardless of orientation or position
	glm::vec3 min;

	//max remains static, regardless of orientation or position
	glm::vec3 max;

	//center remains static, regardless of orientation or position
	glm::vec3 center;

	//The type of algorthim used for generating the bounding box.
	BoundingBoxType type;
};

class BoundingBox {

public:
	BoundingBox() {}

	BoundingBox(const StaticBoundingBox*);

	const glm::vec3& Center() const;

	const glm::vec3& Position() const;

	const std::vector<glm::vec3>& Vertices() const;

	const Orientation& GetOrientation() const;

	void MoveRelative(const glm::vec3&);

	void MoveAbsolute(const glm::vec3&);

	void SetPosition(const glm::vec3&);

	void SetOrientation(const Orientation&);

	CollisionInfo CollidesWith(const BoundingBox&, const glm::vec3&);

	glm::vec3 ConvertAbsolute(glm::vec3) const;

#ifdef _DEBUG
	void BindGL(Camera*);

	void Render();
#endif // _DEBUG

private:

	CollisionInfo TestCollision_Complex(const BoundingBox&, const glm::vec3&);

	const StaticBoundingBox* sbb;

	//position is dynamic, changing possbily every frame.
	glm::vec3 position = glm::vec3(0);

	//orientation is dynamic, changing possibly every frame.
	Orientation orientation = glm::vec3(0, 0, -1);

#ifdef _DEBUG
	ShaderProgram* shader;
	GLuint VertexBuffer;
#endif
};