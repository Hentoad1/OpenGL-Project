
#include "pch.h"

#include "Engine.h"

int main() {

	Engine::Create();

	Window::Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\model.fbx");

	while (!glfwWindowShouldClose(Engine::GetWindow()))
	{
		Engine::Tick();
	}

	glfwTerminate();

	return 0;
}

