#pragma once

#include "pch.h"

#include "Model.h"
#include "ModelLoader.h"

#include "Screen.h"

namespace Window {

	namespace {

		/* --- Variables --- */
		GLFWwindow* window;

		std::list<WorldContent*> content = std::list<WorldContent*>();


		/* --- Callback Functions --- */
		inline void framebuffer_size_callback(GLFWwindow* w, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		inline void cursor_position_callback(GLFWwindow* w, double xpos, double ypos)
		{

		}
	}




	/* --- Functions --- */

	//Creates a new OpenGL Window.
	inline GLFWwindow* Create() {
		ModelLoader::Create();

		//Initalize GLFW
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		//Create Window Object
		window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OPENGL WINDOW", NULL, NULL);


		//Check Window Object
		if (window == NULL)
		{
			glfwTerminate();

			throw std::exception("Failed to create GLFW window");
		}


		//Create OpenGL Context for Window
		glfwMakeContextCurrent(window);


		//Check for Glad
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw std::exception("Failed to initialize GLAD");
		}


		//Set Viewport
		glad_glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);


		//Set Callbacks
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);


		//Set Mouse Cursor Style
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);


		//Stop Overlap
		glEnable(GL_DEPTH_TEST);


		return window;
	}


	//Renders Frame
	inline void Render() {
		//Process Input
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}


		//Clear 
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//Render World
		for (WorldContent* const i : content) {
			i->Render();
		}



		//Manage Events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	inline void ClearContent(std::string name) {
		for (Model* const i : content) {
			delete i;
		}

		content.clear();
	}

	inline void LoadLevel(std::string name) {
		Model* data = ModelLoader::Load(name);

		if (data != nullptr) {
			WorldContent* newContent = new WorldContent(data);

			content.push_back(newContent);
		}
		else {
			std::cout << "it was null" << std::endl;
		}
	}

	/* --- Getters and Setters --- */

	GLFWwindow* GetWindow() {
		return window;
	}
};