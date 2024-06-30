#pragma once

#include "pch.h"

struct Packed_Bone {
	//The current transform this node has from animations.
	glm::mat4 localTransform;


	//Offset matrix move the vertex to the correct spot in global space.
	glm::mat4 offset;


	//The name of the bone.
	std::string name;


	//Any children of the node.
	std::vector<int> childrenIndices;
};

struct Packed_Skeleton {
	std::vector<Packed_Bone> bones;
};