#pragma once

#include "pch.h"

#include "Camera.h"

#include "World.h"

#include "EngineInternal.h"

#include "AssetManager.h"
#include "ShaderManager.h"

class Engine {

public:
	Engine();

	~Engine();

	void Terminate();

	void Update();

	void Draw();

	bool ShouldClose() const;

	Camera* GetCamera() const;

	//World* GetWorld() const;

	int8_t GetKeyState(int);

	Model* LoadModel(const std::string& name);

	Mesh* LoadMesh(Camera*, Model*, const ComponentMeta&);

	Mesh* LoadMesh(Camera*, const std::string& name, const ComponentMeta&);

private:

	AssetManager assetManager;
	ShaderManager shaderManager;

	FrameData currentActionState;
	bool seenMouseMovement;

	Camera* eCamera;
	//World* eWorld;

	GLFWwindow* eWindow;

	double previousDrawTime = 0;
	double previousUpdateTime = 0;

};