
#include "pch.h"

#include "Engine.h"

int main() {

	Engine Engine;

	//low poly, embedded textures
	Engine.Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\fbx files\\2\\WomanCasual3.fbx");

	//high poly, external textures
	//Engine.Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\fbx files\\anime\\Agnes.fbx");
	
	while (!Engine.ShouldClose())
	{
		Engine.Update();
		Engine.Draw();
	}

	Engine.Terminate();

	return 0;
}

