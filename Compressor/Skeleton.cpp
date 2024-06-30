
#include "pch.h"

#include "Constructors.h"

Skeleton ConstructSkeleton(const aiScene* scene) {
	const aiNode* root = scene->mRootNode;

	std::unordered_map<aiString, aiBone*> mesh_bones;

	for (int i = 0; i < scene->mNumMeshes; ++i) {
		const aiMesh* mesh = scene->mMeshes[0];

		for (int i = 0; i < mesh->mNumBones; ++i) {
			
			std::unordered_map<aiString, aiBone*>::const_iterator it = mesh_bones.find(mesh->mBones[0]->mName);

			if (it != mesh_bones.end()) {
				mesh_bones.emplace(mesh->mBones[0]->mName, mesh->mBones[0]);
			}
		}
	}

	bool rootSet = false;
	Bone rootBone;

	auto ProcessNode = [&](aiNode* node, Bone* parent)
		{
			std::unordered_map<aiString, aiBone*>::const_iterator it = mesh_bones.find(node->mName);

			if (it != mesh_bones.end()) {
				
				if (parent == nullptr) {
					aiBone* b = (*it).second;
					
					rootBone = Bone{ b->mOffsetMatrix, };
				}


			}
		};
}

