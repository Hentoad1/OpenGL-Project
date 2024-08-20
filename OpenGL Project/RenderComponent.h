#pragma once

#include "pch.h"
#include "Model.h"

#include "BasicShader.h"
#include "SkeletalShader.h"

#include "AnimationComponent.h"

#include "ComponentData.h"

class RenderComponent {
	
public:
	RenderComponent(ComponentData*, const ComponentMeta*, Model*, ShaderProgram* shader, const AnimationComponent* = nullptr);
	
	~RenderComponent();

	void Render();


private:

	//Shader
	ShaderProgram* shader;

	//Model Data
	Model* model;

	const AnimationComponent* animComp;
};