#pragma once

#include "Camera.h"
#include "BasicMesh.h"

class World {

public:
	World(Camera*);

	~World();

	void Load(std::string);

	void Render();

	glm::vec3 TestCollision(const BoundingBox&);

private:
	Camera* wCamera;

	std::list<Mesh*> content;
};