
#include "pch.h"

#include "Engine.h"
//#include "BoundingBox.h"

/*
int main() {
	
	glm::vec3 polygonAMin = glm::vec3(0.5, 0, 3);
	glm::vec3 polygonAMax = glm::vec3(3, 8, 5);

	glm::vec3 polygonBMin = glm::vec3(-2, 1, 2);
	glm::vec3 polygonBMax = glm::vec3(1, 3, 7);


	BoundingBox a = BoundingBox(polygonAMin, polygonAMax);
	BoundingBox b = BoundingBox(polygonBMin, polygonBMax);

	bool result = a.CollidesWith(b);

	std::cout << "return result: " << result << std::endl;
	
	std::cout << glm::to_string((glm::vec3(0, 5, 2) + glm::vec3(2, 1, 5)) * 0.5f) << std::endl;
	std::cout << glm::to_string(a.Center()) << std::endl;
	std::cout << glm::to_string(b.Center()) << std::endl;

	return 0;
}
*/


int main() {

	//throw;


	


	Engine Engine;

	//rotate image 90 degrees to see if its works. also use the new material system created.
	//throw;

	//low poly, embedded textures
	//Engine.Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\fbx files\\2\\WomanCasual3.fbx");

	//high poly, external textures
	Engine.Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\fbx files\\anime\\Agnes.fbx");
	
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

