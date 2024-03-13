#pragma once

#include "Camera.h"
#include "BasicMesh.h"

class Window {

public:
	Window(Camera*);

	~Window();

	void Load(std::string);

	void Render();

	bool ShouldClose() const;

private:
	GLFWwindow* window;

	Camera* wCamera;

	std::list<Mesh*> content;
};