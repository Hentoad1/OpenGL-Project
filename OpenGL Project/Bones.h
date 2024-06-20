#pragma once

#include "pch.h"

#include "Vertex.h"

struct BoneInfo {
	int index;

	glm::mat4 offset;
};

struct BoneNode {

	int boneIndex;

	std::vector<BoneNode*> children;

	BoneNode* parent;

};

class BoneTree {
public:

	BoneTree(const BoneTree& ref) {
		throw;
	}

	BoneTree(const aiNode* root, const aiMesh* mesh);

	BoneNode* GetBone(const aiString& name);

	std::vector<aiBone*> GetBones() const;

	~BoneTree();

	BoneNode* MapRoot;
	std::unordered_map<std::string, BoneNode*> BoneMap;
	std::vector<aiBone*> bones;

private:
	BoneNode* ProcessNode(const aiNode* node, const aiNode* parent);

};
