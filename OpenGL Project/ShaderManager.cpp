#include "pch.h"

#include "ShaderManager.h"

#include "BasicShader.h"
#include "SkeletalShader.h"

ShaderManager::ShaderManager() {

}

ShaderManager::~ShaderManager() {
	for (const auto& [key, value] : shaders) {
		delete value;
	}
}

ShaderProgram* ShaderManager::Load(MeshShader type, Camera* cam) {
	
	if (shaders.contains(type)) {
		return shaders[type];
	}

	switch (type) {
		case MESH_SHADERTYPE_BASIC: {
			ShaderProgram* program = (ShaderProgram*)(new BasicShader(cam));
			shaders.emplace(type, program);
			return program;
			break;
		}


		case MESH_SHADERTYPE_SKELETAL: {
			ShaderProgram* program = (ShaderProgram*)(new SkeletalShader(cam));
			shaders.emplace(type, program);
			return program;
			break;
		}

	}

	return nullptr;
}