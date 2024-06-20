#include "pch.h"

#include "Bones.h"

BoneTree::~BoneTree() {

	for (const auto& [name, bone] : BoneMap) {
		delete bone;
	}
}

BoneTree::BoneTree(const aiNode* root, const aiMesh* mesh) {

	for (int i = 0; i < mesh->mNumBones; ++i) {
		bones.push_back(mesh->mBones[i]);
	}

	MapRoot = ProcessNode(root, nullptr);

}

BoneNode* BoneTree::ProcessNode(const aiNode* node, const aiNode* parent) {

	int index = -1;
	
	for (int i = 0; i < bones.size(); ++i) {
		if (bones[i]->mName == node->mName) {
			index = i;
			break;
		}
	}

	if (index == -1) {
		if (parent == nullptr) {

			BoneNode* result;
			
			for (int i = 0; i < node->mNumChildren; ++i) {
				result = ProcessNode(node->mChildren[i], nullptr);

				if (result != nullptr) {
					return result;
				}
			}
		}
		else {
			return nullptr;
		}
	}

	BoneNode* boneNode = new BoneNode();

	for (int i = 0; i < node->mNumChildren; ++i) {
		aiNode* child = node->mChildren[i];

		BoneNode* boneChild = ProcessNode(child, node);
		
		if (boneChild != nullptr) {
			boneNode->children.push_back(boneChild);
		}

	}

	BoneMap.emplace(std::string(node->mName.C_Str()), boneNode);

	return boneNode;
}

BoneNode* BoneTree::GetBone(const aiString& name) {
	return BoneMap.at(std::string(name.C_Str()));
}

std::vector<aiBone*> BoneTree::GetBones() const {
	return bones;
}