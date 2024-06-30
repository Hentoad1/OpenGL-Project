#pragma once

#include "pch.h"

struct Bone{
	//The current transform this node has from animations.
	glm::mat4 localTransform;


	//Offset matrix move the vertex to the correct spot in global space.
	glm::mat4 offset;


	//The name of the bone.
	std::string name;


	//Any children of the node.
	std::vector<Bone> children;
};

struct Skeleton {
	Bone RootBone;
};