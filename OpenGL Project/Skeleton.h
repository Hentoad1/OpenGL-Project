#pragma once

#include "pch.h"
#include "Vertex.h"

struct Bone {
	
	Bone(aiBone*, int);

	//The current transform this node has from animations.
	glm::mat4 localTransform;


	//The transformation from the parent node to the current node.
	glm::mat4 Transformation;


	//Offset matrix move the vertex to the correct spot in global space.
	glm::mat4 offset;

	//The index the bone lies in the bones array.
	int index;


	//The name of the bone.
	std::string name;


	//Any children of the node.
	std::vector<Bone*> children;


	//The parent node, nullptr if root.
	Bone* parent;

};

class Skeleton {
private:

	//The root bone to the skeleton
	Bone* rootBone;

	//Array of all of the bones in the skeleton.
	std::vector<Bone*> bones;
	
	//Map connecting bone names to the bone pointers.
	std::unordered_map<std::string, Bone*> boneMap;

	Bone* CreateMap(const aiNode* node, const Bone* parent);

public:

	~Skeleton();

	Skeleton(const aiNode* root, const aiMesh* mesh);

	std::vector<Bone*> GetBones() const;

	Bone* GetBone(const aiString&) const;

	Bone* GetRoot() const;

	void SetVertexBoneData(std::vector<Vertex>&);

};