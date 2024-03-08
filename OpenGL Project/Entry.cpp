
#include "pch.h"

bool DoTheImportThing(const std::string& pFile) {
	// Create an instance of the Importer class
	Assimp::Importer importer;

	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll
	// probably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	// If the import failed, report it
	if (nullptr == scene) {
		std::cout << importer.GetErrorString() << std::endl;
		return false;
	}

	std::cout << scene->HasCameras() << std::endl;
	std::cout << scene->mName.C_Str() << std::endl;

	// Now we can access the file's contents.
	//DoTheSceneProcessing(scene);

	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}

int main() {

	DoTheImportThing("C:\\Users\\henry\\OneDrive\\Documents\\Programming\\Projects\\Visual Studio 2022\\OpenGL\\OpenGL Project\\OpenGL Project\\Assets\\model.fbx");

	return 0;
}

