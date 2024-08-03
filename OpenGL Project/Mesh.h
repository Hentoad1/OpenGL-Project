#pragma once

#include "pch.h"

#include "BasicShader.h"

#include "Model.h"

#include "InputComponent.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"

#include "ComponentData.h"

#include "EngineInternal.h"

enum TextureType : uint8_t {
	TextureType_DIFFUSE = 0,
	TextureType_SPECULAR = 1,
	TextureType_AMBIENT = 2,
};

class Mesh {

public:
	Mesh(const Mesh& ref);

	Mesh(Camera*, Model*, const ComponentMeta&);

	~Mesh();

	void Update(const FrameData&);

	void Render();

	BoundingBox& GetBoundingBox();

	void SetBoundingBox(const BoundingBox&);

	ComponentMeta cMeta;
private:
	
	//Info shared between components
	ComponentData cData;

	//Components
	RenderComponent* cRender;
	PhysicsComponent* cPhysics;
	InputComponent* cInput;
	AnimationComponent* cAnim;

	//Camera
	Camera* mCamera;

	//Shader
	//ShaderProgram* shader;
};