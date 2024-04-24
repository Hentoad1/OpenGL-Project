#pragma once

#include "Camera.h"
#include "World.h"
#include "Config.h"

enum Action {
	ACTION_WALK_FORWARD = GLFW_KEY_W, 
	ACTION_WALK_BACKWARD = GLFW_KEY_S, 
	ACTION_WALK_LEFT = GLFW_KEY_A, 
	ACTION_WALK_RIGHT = GLFW_KEY_D, 
	ACTION_JUMP = GLFW_KEY_SPACE, 
	ACTION_CROUCH = GLFW_KEY_LEFT_CONTROL, 
	ACTION_INTERACT = GLFW_KEY_E
};

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

	World* GetWorld() const;

	int8_t GetKeyState(int);

	glm::dvec2 CursorPos;

private:
	Camera* eCamera;
	World* eWorld;

	GLFWwindow* eWindow;

	double previousDrawTime = 0;
	double previousUpdateTime = 0;


};