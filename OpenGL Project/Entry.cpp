
#include "pch.h"

#include "Engine.h"

#include "CustomImporter.h"

int main() {

	//shaders are about as good as they will get until a full importer is made, just make animations now.
	//animations

	//create a method in storing image data only once. this can allow for efficient batch rendering

	/*
	RENDERING:

	Right now BasicShader stores textures in 3 arrays of uniforms. A more efficient approach would be
	using a Shader Storeage Buffer Object (https://www.khronos.org/opengl/wiki/Shader_Storage_Buffer_Object)
	or a Uniform Buffer Object (https://www.khronos.org/opengl/wiki/Uniform_Buffer_Object)

	//potentially use material struct instead of parallel arrays or just procrastinate for later.
	//this is harder than i thought u cannot make a struct with sampler2D, probably only use uniform buffer object for lights.

	OpenGL does not copy the data placed into a Shader Storeage Buffer Object, so ideally a system would be in place to reuse textures and materials, using minial memory.

	When doing this batch rendering can be done very efficiently. All the data of a material can be placed into one of these buffers, and then every object using that material is rendered.

	*/

	/*
	PHYSICS:
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
	* 
	* clean up scuffed callbacks
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
		MESH_USECOLLISION | 

		MESH_SHADERTYPE_BASIC 
	);

	World::Load(warwick);

	//load player

	ModelBuffers* m = new ModelBuffers{ 0, std::vector<MaterialBuffer*>(), std::vector<SubMesh>(), glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1) };

	Mesh* player = new Mesh(
		Engine.GetCamera(),
		m,
		MESH_COMPONENT_PHYSICS |
		MESH_COMPONENT_INPUT |

		MESH_USECOLLISION |
		MESH_ATTACHEDCAMERA |

		MESH_SHADERTYPE_BASIC
	);
	
	World::Load(player);

	while (!Engine.ShouldClose())
	{
		Engine.Update();
		Engine.Draw();
	}

	Engine.Terminate();

	delete m;

	return 0;
}

