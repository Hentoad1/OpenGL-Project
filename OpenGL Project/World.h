#pragma once

#include "Camera.h"

#include "Mesh.h"
//#include "BasicMesh.h"
//#include "PhysicsMesh.h"
//#include "CameraMesh.h"

#include "ModelData.h"

#include "EngineInternal.h"

namespace World{

	void Create(Camera*);

	void Destory();

	void Load(Mesh*);

	//void Load(const std::string&);

	//why the hell is this here?
	//void Load(Mesh*, bool);

	void Render();

	void Update(const FrameData&);

	bool TestCollision(const BoundingBox&);

	CollisionInfo TestCollision(const BoundingBox&, const glm::vec3&);

}