
#include "pch.h"
#include "World2.h"

#include "EngineInternal.h"

World::World(Camera* wCam) {
	content = std::list<Mesh*>();
	wCamera = wCam;
}

World::~World() {
	
	for (auto it = content.begin(); it != content.end(); ++it) {
		delete* it;
	}

	content.clear();
}

void World::Load(const std::string& path) {
	Mesh* newContent = new Mesh(path, wCamera);

	content.push_back(newContent);
}

void World::Load(Mesh* mesh) {
	content.push_back(mesh);
}

void World::Render() {
	for (auto it = content.begin(); it != content.end(); ++it) {
		(*it)->Render();
	}
}

void World::Update(const FrameData& state) {
	for (auto it = content.begin(); it != content.end(); ++it) {
		(*it)->Update(state);
	}
}

glm::vec3 World::TestCollision(const BoundingBox& other) {

	for (auto it = content.begin(); it != content.end(); ++it) {
		if ((*it)->CollidesWith(other)) {
			std::cout << "Collision found" << std::endl;
		}
	}

	return glm::vec3(0);
}