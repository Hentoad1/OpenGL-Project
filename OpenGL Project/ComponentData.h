#pragma once

#include "pch.h"

#include "BoundingBox.h"
#include "Camera.h"

enum ShaderType : uint8_t {
	SHADERTYPE_BASIC = 1
	//SHADERTYPE_BASIC = 2
	//SHADERTYPE_BASIC = 3
	//SHADERTYPE_BASIC = 4
};

/*
This is the components the mesh uses. THere can be zero, one, or many.
*/
enum MeshComponent : uint8_t {

	MESH_COMPONENT_RENDER =		0b00000001,
	MESH_COMPONENT_PHYSICS =	0b00000010,
	MESH_COMPONENT_INPUT =		0b00000100,
	MESH_COMPONENT_ANIMATION =	0b00001000,

	//MESH_COMPONENT_EMPTY =	0b00010000,
	//MESH_COMPONENT_EMPTY =	0b00100000,
	//MESH_COMPONENT_EMPTY =	0b01000000,
	//MESH_COMPONENT_EMPTY =	0b10000000,

};

/*
This is the shader the mesh uses. The must be only one, no more or less.
*/
enum MeshShader : uint8_t {

	MESH_SHADERTYPE_NONE =		0b00000000,
	MESH_SHADERTYPE_BASIC =		0b00000001,
	MESH_SHADERTYPE_SKELETAL =	0b00000010,

	//MESH_SHADERTYPE_EMPTY =	0b00000100,
	//MESH_SHADERTYPE_EMPTY =	0b00001000,
	//MESH_SHADERTYPE_EMPTY =	0b00010000,
	//MESH_SHADERTYPE_EMPTY =	0b00100000,
	//MESH_SHADERTYPE_EMPTY =	0b01000000,
	//MESH_SHADERTYPE_EMPTY =	0b10000000,

};


/*
These are options for how the mesh behaves, there can be zero, one, or many.
*/
enum MeshOptions : uint8_t {

	MESH_OPTION_USECOLLISION =			0b00000001,
	MESH_OPTION_ATTACHEDCAMERA =		0b00000010,

	//MESH_OPTION_EMPTY =			0b00000100,
	//MESH_OPTION_EMPTY =			0b00001000,
	//MESH_OPTION_EMPTY =			0b00010000,
	//MESH_OPTION_EMPTY =			0b00100000,
	//MESH_OPTION_EMPTY =			0b01000000,
	//MESH_OPTION_EMPTY =			0b10000000,

};

struct ComponentMeta {
public:
	
	ComponentMeta(MeshShader s, uint8_t c, uint8_t o) : shader(s), component(c), options(o) {}

	bool has(const MeshShader& o) const {
		return shader == o;
	}

	bool has(const MeshComponent& o) const {
		return (component & o);
	}	

	bool has(const MeshOptions& o) const {
		return options & o;
	}
	
	MeshShader GetShader() const {
		return shader;
	}

private:
	MeshShader shader;
	uint8_t component;
	uint8_t options;
};

/*struct ComponentMeta {

	bool RenderComp : 1;
	bool PhysicsComp : 1;
	bool InputComp : 1;

	bool hasCollision : 1;
	bool hasAttachedCamera : 1;

	ShaderType shaderType : 2;
	//....
};*/

struct ComponentData {

	BoundingBox bounds;

	Camera* camera;

	glm::vec3 velocity;

};