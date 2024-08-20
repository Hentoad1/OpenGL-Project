#pragma once

#include "Shader.h"
#include "ComponentData.h"

class ShaderManager {

public:
	ShaderManager();

	~ShaderManager();


	//modify component meta struct so that shader type is a stored value in the struct doesnt require bit shift to check.
	ShaderProgram* Load(MeshShader, Camera* cam);

private:
	std::unordered_map<MeshShader, ShaderProgram*> shaders;

};