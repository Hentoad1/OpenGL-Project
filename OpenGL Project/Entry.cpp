
#include "pch.h"

#include "Engine.h"

int main() {

	/*
	* collision does not work at high speeds. The coefficient is fucked. 
	* 
	* 
	* Maybe take reverse velocity and project it to get dot products and 
	* then generate a coefficient in terms of how many 1D projected velocity lengths it would take to reach min / max?
	* 	
	* 
	* The World is a bandaid solution on bandaid solution.
	* Remove physics object list and instead have one list but take mesh pointer so you can test if they are equal or not.
	* Eventually use the thing in minecraft to save time like octoids or some shit
	* 
	* 
	* 
	* remove testing shit for collision
	* octoids
	*/

	


	Engine Engine;

	//rotate image 90 degrees to see if its works. also use the new material system created.
	//throw;

	//low poly, embedded textures
	//Engine.Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\fbx files\\2\\WomanCasual3.fbx");

	//high poly, external textures
	World::Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\fbx files\\anime\\Agnes.fbx");
	
	CameraMesh* a = new CameraMesh(BoundingBox(glm::vec3(0,0,30), glm::vec3(1, 1, 31)), Engine.GetCamera());

	World::Load((Mesh*)a, false);

	//has big ass box and no textures
	//Engine.Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\fbx files\\shit anime\\model.fbx");

	//barrel
	//Engine.Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\fbx files\\barrel\\wooden_barrel.fbx");

	//chair
	//Engine.Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\fbx files\\chair\\chair.fbx");

	//jeep
	//Engine.Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\fbx files\\jeep\\Jeep_Renegade_2016.fbx");

	while (!Engine.ShouldClose())
	{
		Engine.Update();
		Engine.Draw();
	}

	Engine.Terminate();

	return 0;
}

