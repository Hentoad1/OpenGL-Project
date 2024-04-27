#pragma once

#include "pch.h"
#include "BasicMesh.h"

class PhysicsMesh : Mesh{

public:
	PhysicsMesh(const std::string&, Camera* mCam);

	PhysicsMesh(const BoundingBox&, Camera*);

	~PhysicsMesh();

	void Update(const InputState&) override;

	//put things like velocity, physics, and collision here.

	virtual void AccelerateRelative(glm::vec3);
	virtual void AccelerateAbsolute(glm::vec3);

protected:
	Camera* GetCamera() override {
		return Mesh::GetCamera();
	}

	BoundingBox& GetBoundingBox() override {
		return Mesh::GetBoundingBox();
	}
private:

	glm::vec3 velocity;
};