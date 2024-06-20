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

enum ComponentOptions {
	MESH_COMPONENT_RENDER =		0b0000000000000001,
	MESH_COMPONENT_PHYSICS =	0b0000000000000010,
	MESH_COMPONENT_INPUT =		0b0000000000000100,
	MESH_COMPONENT_ANIMATION =	0b0000000000001000,

	//MESH_COMPONENT_EMPTY =	0b0000000000010000,
	//MESH_COMPONENT_EMPTY =	0b0000000000100000,
	//MESH_COMPONENT_EMPTY =	0b0000000001000000,
	//MESH_COMPONENT_EMPTY =	0b0000000010000000,

	MESH_USECOLLISION =			0b0000000100000000,
	MESH_ATTACHEDCAMERA =		0b0000001000000000,
	//MESH_EMPTY_FLAG =			0b0000010000000000,
	//MESH_EMPTY_FLAG =			0b0000100000000000,
	//MESH_EMPTY_FLAG =			0b0001000000000000,

	MESH_SHADERTYPE_BASIC =		0b0010000000000000,
	MESH_SHADERTYPE_SKELETAL =	0b0100000000000000,
	//MESH_SHADERTYPE_EMPTY =	0b0110000000000000,
};

struct ComponentMeta {
public:
	
	ComponentMeta(uint16_t _) : priv(_) {}

	bool has(const ComponentOptions& o) const {
		return (o == (priv & o));
	}

private:
	uint16_t priv;
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