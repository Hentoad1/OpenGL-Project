#include "pch.h"

#include "Skeleton.h"

Bone::Bone(aiBone* b, int i) : index(i) {
	name = std::string(b->mName.C_Str());
	offset = aiMatrix4x4ToGlm(b->mOffsetMatrix);
	localTransform = glm::mat4(1.0f);

}

Skeleton::~Skeleton() {

	

}

Skeleton::Skeleton(const aiNode* root, const aiMesh* mesh) {

	for (int i = 0; i < mesh->mNumBones; ++i) {
		Bone* newBone = new Bone(mesh->mBones[i], i);

		std::cout << mesh->mBones[i]->mName.C_Str() << std::endl;

		bones.push_back(newBone);
		boneMap.emplace(std::string(mesh->mBones[i]->mName.C_Str()), newBone);
	}

	rootBone = CreateMap(root, nullptr);

}

Bone* Skeleton::GetRoot() const {
	return rootBone;
}

std::vector<Bone*> Skeleton::GetBones() const {
	return bones;
}

Bone* Skeleton::GetBone(const aiString& name) const {
	
	std::unordered_map<std::string, Bone*>::const_iterator it = boneMap.find(std::string(name.C_Str()));

	if (it == boneMap.end()) {
		return nullptr;
	}
	else {
		return (*it).second;
	}

}

Bone* Skeleton::CreateMap(const aiNode* node, const Bone* parent) {

	Bone* bone = GetBone(node->mName);

	std::cout << node->mName.C_Str() << std::endl;

	if (bone == nullptr) {

		/*
		Sometimes the root node is a parent of the root bone.
		So if the bone that is found is null an attempt to find the root bone is made.

		The first child in the bone list is used.
		*/

		if (parent == nullptr) {

			Bone* result;

			for (int i = 0; i < node->mNumChildren; ++i) {
				result = CreateMap(node->mChildren[i], nullptr);

				if (result != nullptr) {
					return result;
				}
			}
		}
		else {
			return nullptr;
		}
	}

	for (int i = 0; i < node->mNumChildren; ++i) {
		aiNode* child = node->mChildren[i];

		Bone* boneChild = CreateMap(child, bone);

		if (boneChild != nullptr) {
			bone->children.push_back(boneChild);
		}

	}

	return bone;

}

void Skeleton::SetVertexBoneData(std::vector<Vertex>&) {

}