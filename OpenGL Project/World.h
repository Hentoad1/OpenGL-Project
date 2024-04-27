#pragma once

#include "Camera.h"

#include "BasicMesh.h"
#include "PhysicsMesh.h"
#include "CameraMesh.h"

#include "EngineInternal.h"

class World {

public:
	World(Camera*);

	~World();

	void Load(const std::string&);

	void Load(Mesh*);

	void Render();

	void Update(const InputState&);

	glm::vec3 TestCollision(const BoundingBox&);

private:
	Camera* wCamera;

	std::list<Mesh*> content;
};