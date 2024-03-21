#include "pch.h"
#include "Vertex.h"

Vertex::Vertex(float x, float y, float z, float uvx, float uvy, float nx, float ny, float nz) {
	position_x = x;
	position_y = y;
	position_z = z;

	texture_x = uvx;
	texture_y = uvy;

	normal_x = nx;
	normal_y = ny;
	normal_z = nz;
}

Vertex::Vertex(const aiVector3D& pos, const aiVector3D& uv, const aiVector3D& normal) {
	position_x = pos.x;
	position_y = pos.y;
	position_z = pos.z;

	texture_x = uv.x;
	texture_y = uv.y;

	normal_x = normal.x;
	normal_y = normal.y;
	normal_z = normal.z;
}

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

void Vertex::SetTexture(const glm::vec2& uv) {
	texture_x = uv.x;
	texture_y = uv.y;
}

void Vertex::SetTexture(const aiVector3D& uv) {
	texture_x = uv.x;
	texture_y = uv.y;
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