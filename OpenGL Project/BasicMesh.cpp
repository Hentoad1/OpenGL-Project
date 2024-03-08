
#include "BasicMesh.h"

Mesh::Mesh(std::string path) {
	//scene.mNumMeshes
}

aiScene* Mesh::Load(std::string path) {
	Assimp::Importer importer;

	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll
	// probably to request more postprocessing than we do in this example.
	aiScene* scene = (aiScene*)importer.ReadFile(path,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (nullptr == scene) {
		std::cout << importer.GetErrorString() << std::endl;
		throw;
	}

	return scene;
}