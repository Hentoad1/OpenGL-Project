
#include "pch.h"
#include "World.h"

#include "EngineInternal.h"

static Camera* wCamera;

static std::list<Mesh*> physicsObjects;
static std::list<Mesh*> content;

void World::Create(Camera* wCam) {
	content = std::list<Mesh*>();
	wCamera = wCam;
}

void World::Destory() {

	for (auto it = content.begin(); it != content.end(); ++it) {
		delete* it;
	}

	content.clear();
}

/*void World::Load(const std::string& path) {
	Mesh* newContent = new Mesh(path, wCamera);

	content.push_back(newContent);
	physicsObjects.push_back(newContent);
}

void World::Load(Mesh* mesh, bool physics) {
	content.push_back(mesh);
	if (physics) {
		physicsObjects.push_back(mesh);
	}

}*/

void World::Load(Mesh* m) {
	content.push_back(m);

	if (m->cMeta.has(MESH_USECOLLISION)) {
		physicsObjects.push_back(m);
	}
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

bool World::TestCollision(const BoundingBox& other) {
	for (auto it = physicsObjects.begin(); it != physicsObjects.end(); ++it) {
		Mesh* mesh = (*it);

		if ((*it)->GetBoundingBox().CollidesWith(other)) {
			return true;
		}
		
	}

	return false;
}

CollisionInfo World::TestCollision(const BoundingBox& other, const glm::vec3& otherVelocity) {

	for (auto it = physicsObjects.begin(); it != physicsObjects.end(); ++it) {
		CollisionInfo info = (*it)->GetBoundingBox().CollidesWith(other, otherVelocity);

		if (info.collided) {
			return info;
		}
	}

	return CollisionInfo{false};
}