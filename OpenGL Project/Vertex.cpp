#include "pch.h"
#include "Vertex.h"

Vertex::Vertex() {}

Vertex::~Vertex() {}

void Vertex::SetPosition(const glm::vec3& pos) {
	position_x = pos.x;
	position_y = pos.y;
	position_z = pos.z;
}

void Vertex::SetPosition(const aiVector3D& pos) {
	position_x = pos.x;
	position_y = pos.y;
	position_z = pos.z;
}

void Vertex::SetTexture(const glm::vec2& cords) {
	texture_x = cords.x;
	texture_y = cords.y;
}

void Vertex::SetTexture(const aiVector3D& cords) {
	texture_x = cords.x;
	texture_y = cords.y;
}

void Vertex::SetNormal(const glm::vec3& normal) {
	normal_x = normal.x;
	normal_y = normal.y;
	normal_z = normal.z;
}

void Vertex::SetNormal(const aiVector3D& normal) {
	normal_x = normal.x;
	normal_y = normal.y;
	normal_z = normal.z;
}

glm::vec3 Vertex::GetPosition() const {
	return glm::vec3(position_x, position_y, position_z);
}

glm::vec2 Vertex::GetTexture() const {
	return glm::vec2(texture_x, texture_y);
}

glm::vec3 Vertex::GetNormal() const {
	return glm::vec3(normal_x, normal_y, normal_z);
}