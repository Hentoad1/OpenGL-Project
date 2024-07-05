#include "pch.h"

#include "BoundingBox.h"

#ifdef _DEBUG
#include "DebugShader.h"
#endif // _DEBUG



BoundingBox::BoundingBox(const StaticBoundingBox* _sbb) : sbb(_sbb) {}

const glm::vec3& BoundingBox::Center() const {
	return position + sbb->center;
}

const glm::vec3& BoundingBox::Position() const {
	return position;
}

const std::vector<glm::vec3>& BoundingBox::Vertices() const {
	return sbb->vertices;
}

const Orientation& BoundingBox::GetOrientation() const {
	return orientation;
}

void BoundingBox::SetPosition(const glm::vec3& value) {
	position = value;
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
}

void BoundingBox::MoveAbsolute(const glm::vec3& delta) {
	position += delta;
}

glm::vec3 BoundingBox::ConvertAbsolute(glm::vec3 value) const {
	AxisVectors directions = GetOrientation().GetAxis();

	return 
		(glm::vec3(value.x) * directions.Front) +
		(glm::vec3(value.y) * directions.Up) +
		(glm::vec3(value.z) * directions.Right);
}


CollisionInfo BoundingBox::CollidesWith(const BoundingBox& boxB, const glm::vec3& velocity) {
	return TestCollision_Complex(boxB, velocity);
}


#ifdef _DEBUG

void BoundingBox::BindGL(Camera* bCam){

	shader = (ShaderProgram*)new DebugShader(bCam, Position());

	GLuint mBuffers[2];

	glGenVertexArrays(1, &VertexBuffer);
	glBindVertexArray(VertexBuffer);

	glGenBuffers(2, mBuffers);

	size_t Vertex_Size = sizeof(sbb->vertices[0]);

	glBindBuffer(GL_ARRAY_BUFFER, mBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER, Vertex_Size * sbb->vertices.size(), &sbb->vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, Vertex_Size, 0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mBuffers[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(sbb->indices[0]) * sbb->indices.size(), &sbb->indices[0], GL_STATIC_DRAW);
	
	glBindVertexArray(0);
}

void BoundingBox::Render() {

	shader->SetPosition(Position());

	shader->Use();

	shader->Update();

	glBindVertexArray(VertexBuffer);

	glDrawElements(GL_LINES, sbb->indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

#endif // _DEBUG