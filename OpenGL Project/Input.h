#pragma once

/*
Callbacks:

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
			Cam->Rotate(true, amount);
			break;
		case(GLFW_KEY_LEFT):
			Cam->Rotate(true, -amount);
			break;
		case(GLFW_KEY_UP):
			Cam->Rotate(false, amount);
			break;
		case(GLFW_KEY_DOWN):
			Cam->Rotate(false, -amount);
			break;
		default:
			break;
		}
	}

	void onMouseWheel(GLFWwindow* window, double xoffset, double yoffset) {
		Cam->Zoom(yoffset);
	}

	inline void framebuffer_size_callback(GLFWwindow* w, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		inline void cursor_position_callback(GLFWwindow* w, double xpos, double ypos)
		{

		}


	glfwSetKeyCallback(Window::GetWindow(), onInput);
	glfwSetScrollCallback(Window::GetWindow(), onMouseWheel);

*/