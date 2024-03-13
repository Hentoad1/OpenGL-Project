
#include "pch.h"
#include "Engine.h"

Engine::Engine() {
	cam = new Camera();
	win = new Window(cam);
}

Engine::~Engine() {
	delete cam;
	delete win;
}

void Engine::Tick() {
	win->Render();
}

/* --------------------------------- GETTERS AND SETTERS --------------------------------- */

bool Engine::ShouldClose() const {
	return win->ShouldClose();
}