#pragma once

#include "Camera.h"
#include "Window.h"

class Engine {

public:
	Engine();

	~Engine();

	void Tick();

	bool ShouldClose() const;

private:
	Camera* cam;
	Window* win;
};