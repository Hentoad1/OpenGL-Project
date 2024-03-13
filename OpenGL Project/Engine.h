#pragma once

#include "Camera.h"
#include "World.h"

class Engine {

public:
	Engine();

	~Engine();

	void Terminate();

	void Load(std::string);

	void Update();

	void Draw();


	bool ShouldClose() const;

private:
	Camera* eCamera;
	World* eWorld;

	GLFWwindow* eWindow;
};