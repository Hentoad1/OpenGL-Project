#pragma once

#include "pch.h"

#include "Window.h"

namespace Engine {

	/* --- Variables --- */

	enum ENGINE_SETTING : char {
		DEFAULT = 1,
		VIEW_MESH = 2,
		EDIT_LEVEL = 3
	};

	ENGINE_SETTING setting = DEFAULT;

	/* --- Callback Functions --- */

	void onInput(GLFWwindow* window, int key, int scancode, int action, int mods) {
		float amount = 0.2f;

		if (action == GLFW_REPEAT) {
			amount = 0.1f;
		}
		else if (action == GLFW_RELEASE) {
			return;
		}

		switch (key)
		{
		case(GLFW_KEY_RIGHT):
			Camera::Rotate(true, amount);
			break;
		case(GLFW_KEY_LEFT):
			Camera::Rotate(true, -amount);
			break;
		case(GLFW_KEY_UP):
			Camera::Rotate(false, amount);
			break;
		case(GLFW_KEY_DOWN):
			Camera::Rotate(false, -amount);
			break;
		default:
			break;
		}
	}

	void onMouseWheel(GLFWwindow* window, double xoffset, double yoffset) {
		Camera::Zoom(yoffset);
	}

	/* --- Functions --- */

	void Create() {
		Camera::Create();

		Window::Create();

		glfwSetKeyCallback(Window::GetWindow(), onInput);
		glfwSetScrollCallback(Window::GetWindow(), onMouseWheel);

	}

	void Tick() {
		Window::Render();
	}

	/* --- Getters and Setters --- */

	GLFWwindow* GetWindow() {
		return Window::GetWindow();
	}
};