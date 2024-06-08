#pragma once

#include "pch.h"
#include "ModelData.h"

#include "BasicShader.h"

#include "ComponentData.h"

class RenderComponent {
	
public:
	RenderComponent(ComponentData*, const ComponentMeta*, const ModelBuffers*);
	
	~RenderComponent();

	void Render();

private:

	//Shader
	ShaderProgram* shader;

	//Model Data
	const ModelBuffers* mData;

};