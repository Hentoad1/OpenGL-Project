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
	MESH_COMPONENT_RENDER =		0b0000001,
	MESH_COMPONENT_PHYSICS =	0b0000010,
	MESH_COMPONENT_INPUT =		0b0000100,

	MESH_USECOLLISION =			0b0001000,
	MESH_ATTACHEDCAMERA =		0b0010000,

	MESH_SHADERTYPE_BASIC =		0b0000000,
	MESH_SHADERTYPE_2 =			0b0100000,
	MESH_SHADERTYPE_3 =			0b1000000,
	MESH_SHADERTYPE_4 =			0b1100000,
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