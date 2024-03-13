#pragma once

#include "Camera.h"
#include "BasicMesh.h"

class World {

public:
	World(Camera*);

	~World();

	void Load(std::string);

	void Render();

private:
	Camera* wCamera;

	std::list<Mesh*> content;
};