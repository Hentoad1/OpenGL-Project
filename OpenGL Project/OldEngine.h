#pragma once

#include "pch.h"

#include "Window.h"
#include "Camera.h"

/*

when converting to a class try glfwMakeContextCurrent
*/

namespace Engine {

	namespace {
		Camera* Cam;
	}

	/* --------------------------------- CALLBACK FUNCTIONS ---------------------------------- */

	

	/* -------------------------------------- FUNCTIONS -------------------------------------- */

	void Create() {
		Cam = new Camera();

		Window::Create(Cam);

		glfwSetKeyCallback(Window::GetWindow(), onInput);
		glfwSetScrollCallback(Window::GetWindow(), onMouseWheel);

	}

	void Tick() {
		Window::Render();
	}

	void Delete() {
		delete Cam;
	}

	/* --------------------------------- GETTERS AND SETTERS --------------------------------- */

	GLFWwindow* GetWindow() {
		return Window::GetWindow();
	}
};