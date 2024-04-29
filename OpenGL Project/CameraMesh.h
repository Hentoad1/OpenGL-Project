#pragma once

#include "pch.h"
#include "PhysicsMesh.h"

class CameraMesh : PhysicsMesh {

public:
	CameraMesh(const std::string&, Camera* mCam);

	CameraMesh(const BoundingBox&, Camera* mCam);

	~CameraMesh();

	void Update(const FrameData&) override;

	//put things like velocity, physics, and collision here.

	Camera* GetCamera();
 private:


};