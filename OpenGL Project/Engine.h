#pragma once

#include "Camera.h"
#include "World.h"
#include "Config.h"

class Engine {

public:
	Engine();

	~Engine();

	void Terminate();

	void Load(std::string);

	void Update();

	void Draw();

	bool ShouldClose() const;

	Camera* GetCamera() const;

	glm::dvec2 CursorPos;

private:
	Camera* eCamera;
	World* eWorld;

	GLFWwindow* eWindow;

	double previousDrawTime = 0;
	double previousUpdateTime = 0;


};