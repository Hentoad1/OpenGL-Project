
#include "pch.h"
#include "World.h"

#include "Screen.h"

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

void World::Load(std::string path) {
	Mesh* newContent = new Mesh(path, wCamera);

	content.push_back(newContent);
}

void World::Render() {
	for (auto it = content.begin(); it != content.end(); ++it) {
		(*it)->Render();
	}
}