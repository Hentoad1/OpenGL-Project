#include "pch.h"

#include "PhysicsMesh.h"

PhysicsMesh::PhysicsMesh(const std::string& file, Camera* mCam) : Mesh(file, mCam) {}

PhysicsMesh::PhysicsMesh(const BoundingBox& bounds, Camera* mCam) : Mesh(bounds, mCam) {}

PhysicsMesh::~PhysicsMesh() {
	Mesh::~Mesh();
}

void PhysicsMesh::Update(const InputState&) {

}

//these are temporary
void PhysicsMesh::AccelerateRelative(glm::vec3 v) {
	GetBoundingBox().MoveRelative(v);
}

void PhysicsMesh::AccelerateAbsolute(glm::vec3 v) {
	GetBoundingBox().MoveRelative(v);
}