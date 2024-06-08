
#include "pch.h"

#include "Engine.h"

#include "CustomImporter.h"

int main() {

	/*
	* The velocity needs to be inverted along the collision axis and then multiplied by negative one 
	* (possbily something that lowers the speed a bit like -0.5).
	* Collision also has allow a person to move alongside a wall without inverting the velocity, but high speed crashes should bounce (hopefully)
	* 
	* 
	* Also the collision is a bit fucked, will be obvious if it works fully or not once the velocity is fixed.
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

	//CameraMesh* a = new CameraMesh(BoundingBox(glm::vec3(0, 0, 30), glm::vec3(1, 1, 31)), Engine.GetCamera());

	//World::Load((Mesh*)a, false);

	//low poly, embedded textures
	//Engine.Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\fbx files\\2\\WomanCasual3.fbx");

	//high poly, external textures
	//World::Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\fbx files\\anime\\Agnes.fbx");
	

	//has big ass box and no textures
	//Engine.Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\fbx files\\shit anime\\model.fbx");

	//barrel
	//Engine.Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\fbx files\\barrel\\wooden_barrel.fbx");

	//chair
	//Engine.Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\fbx files\\chair\\chair.fbx");

	//jeep
	//Engine.Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\fbx files\\jeep\\Jeep_Renegade_2016.fbx");

	//WARWICK
	//World::Load("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\warwick.glb");
	
	CustomImporter importer = CustomImporter();

	ModelBuffers* z = importer.ImportAndAttach("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\warwick.glb");

	Mesh* warwick = new Mesh(
		Engine.GetCamera(),
		z,
		MESH_COMPONENT_RENDER |
		MESH_COMPONENT_PHYSICS |
		MESH_COMPONENT_INPUT |

		MESH_USECOLLISION | 
		MESH_ATTACHEDCAMERA | 

		MESH_SHADERTYPE_BASIC 
	);
	
	World::Load(warwick);

	while (!Engine.ShouldClose())
	{
		Engine.Update();
		Engine.Draw();
	}

	Engine.Terminate();

	

	return 0;
}

