#pragma once

#include "pch.h"
#include "ModelData.h"

#include "BasicShader.h"
#include "SkeletalShader.h"

#include "AnimationComponent.h"

#include "ComponentData.h"

class RenderComponent {
	
public:
	RenderComponent(ComponentData*, const ComponentMeta*, const ModelBuffers*, const AnimationComponent* = nullptr);
	
	~RenderComponent();

	void Render();


private:

	//Shader
	ShaderProgram* shader;

	//Model Data
	const ModelBuffers* mData;

	ComponentData* cData;

	const AnimationComponent* animComp;


};