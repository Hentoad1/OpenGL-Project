
#include "pch.h""

#include "Engine.h"

#include "CustomImporter.h"

#include "MemoryMapper.h"

#include "AssetManager.h"

#include "ConvexHull.h"

#include "BoundingBox.h"

int main() {

	/*
	bounding box is always a cube
	cant import meshes

	make it so mesh doesnt construct bounding box to then replace later.
	*/

	/*
	lots of loose ends here.
	A shit ton of debug cout calls
	*/


	//shaders are about as good as they will get until a full importer is made, just make animations now.
	//animations
	

	//create a method in storing image data only once. this can allow for efficient batch rendering

	//create an interface of behaviorComponent to provide unique physics for different meshes

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
	

	//import keyframe

	BuildModels();

	AssetManager assetManager;

	ModelBuffers* ww = assetManager.Attach(assetManager.LoadModel("warwick"));

	Mesh* warwick = new Mesh(
		Engine.GetCamera(),
		ww,
		MESH_COMPONENT_RENDER | 
		MESH_COMPONENT_ANIMATION |
		MESH_USECOLLISION | 

		MESH_SHADERTYPE_SKELETAL
	);

	//warwick->SetBoundingBox(BoundingBox());


	World::Load(warwick);

	ModelData* cannon_raw = assetManager.LoadModel("Cannon");
	ModelBuffers* cannon = assetManager.Attach(cannon_raw);


	//maybe just make an enum for bounding box type and then have 1 goated constructor for boundingbox that recives all data for all boxes

	BoundingBox bounds = CreateConvexHull(*static_cast<std::vector<Vertex>*>(cannon_raw->vertices));



	Mesh* other = new Mesh(
		Engine.GetCamera(),
		cannon,
		bounds,
		MESH_COMPONENT_RENDER |
		MESH_USECOLLISION |

		MESH_SHADERTYPE_BASIC
	);

	World::Load(other);

	//warwick->SetBoundingBox(CreateConvexHull());

	//load player

	ModelBuffers* m1 = new ModelBuffers{ 0, std::vector<MaterialBuffer*>(), std::vector<SubMesh>(), nullptr, std::vector<Animation*>(), glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1)};

	Mesh* player = new Mesh(
		Engine.GetCamera(),
		m1,
		MESH_COMPONENT_PHYSICS |
		MESH_COMPONENT_INPUT |

		//MESH_USECOLLISION |
		MESH_ATTACHEDCAMERA |

		MESH_SHADERTYPE_BASIC
	);

	World::Load(player);



	//wall one
	
	/*ModelBuffers* m2 = new ModelBuffers{0, std::vector<MaterialBuffer*>(), std::vector<SubMesh>(), nullptr, std::vector<Animation*>(), glm::vec3(-500, -500, -500), glm::vec3(500, 500, -490)};

	Mesh* wall1 = new Mesh(
		Engine.GetCamera(),
		m2,
		MESH_USECOLLISION |

		MESH_SHADERTYPE_BASIC
	);

	World::Load(wall1);

	//wall two

	ModelBuffers* m3 = new ModelBuffers{ 0, std::vector<MaterialBuffer*>(), std::vector<SubMesh>(), nullptr, std::vector<Animation*>(), glm::vec3(-500, -500, -490), glm::vec3(-490, 500, 500) };

	Mesh* wall2 = new Mesh(
		Engine.GetCamera(),
		m3,
		MESH_USECOLLISION |

		MESH_SHADERTYPE_BASIC
	);

	World::Load(wall2);

	//floor

	ModelBuffers* m4 = new ModelBuffers{ 0, std::vector<MaterialBuffer*>(), std::vector<SubMesh>(), nullptr, std::vector<Animation*>(), glm::vec3(-490, -500, -490), glm::vec3(500, -490, 500) };

	Mesh* floor = new Mesh(
		Engine.GetCamera(),
		m4,
		MESH_USECOLLISION |

		MESH_SHADERTYPE_BASIC
	);

	World::Load(floor);*/

	while (!Engine.ShouldClose())
	{
		Engine.Update();
		Engine.Draw();
	}

	Engine.Terminate();

	delete m1;
	//delete m2;
	//delete m3;
	//delete m4;

	return 0;
}

