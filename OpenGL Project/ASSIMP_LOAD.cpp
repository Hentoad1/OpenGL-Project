#include "pch.h"

#include "MemoryMapper.h"

#include "BuildBoundingBox.h"

ModelData* ASSIMP_LOAD(const std::string& path) {
	/* ------------------------------------ IMPORT SCENE ------------------------------------- */

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(path,

		//required: only want triangles
		aiProcess_Triangulate | \

		//required: want to re-use indices
		aiProcess_JoinIdenticalVertices | \

		//required: creates sub-meshes
		aiProcess_SortByPType | \

		//removes bones and animations, aligning vertices to where they would be.
		//aiProcess_PreTransformVertices | \

		//does fix current issue but is good nonetheless
		aiProcess_GenUVCoords | \

		//max amounts of bones per vertex (defaults to 4) THIS CAUSED AN ERROR. (node tree missing bone segment and not fusing children)
		//aiProcess_LimitBoneWeights | \

		//creates bone nodes for proper importing.
		aiProcess_PopulateArmatureData | \

		//validates that everything is correct
		//aiProcess_ValidateDataStructure | \



		//sometimes this fixes something, sometimes it doesn't
		//aiProcess_FlipUVs | \

		//can be useful later for lighting
		//aiProcess_CalcTangentSpace | \

		//find degenerates
		//aiProcess_FindDegenerates | \

		//takes a lot of import time, but improves optimizations; useful when memory mapping.
		//aiProcess_ImproveCacheLocality | \

		//removes unnecessary texures
		//aiProcess_RemoveRedundantMaterials | \

		//more optimizations
		//aiProcess_OptimizeMeshes | \
			//aiProcess_OptimizeGraph | \

			//infacing normals will be flipped.
			//aiProcess_FixInfacingNormals | \

			//useful for fixing errors, removing bad normals and such
			//aiProcess_FindInvalidData | \

			//Smooth normal will be generated on top of any bad normals
			//aiProcess_GenSmoothNormals | \
			
		0
	);

	if (nullptr == scene) {
		std::cout << importer.GetErrorString() << std::endl;
		throw;
	}





	bool isSkeletal = scene->HasAnimations();

	/* --------------------------------- CREATE BUFFER DATA ---------------------------------- */

	std::vector<Vertex> vertices;
	std::vector<sVertex> sVertices;

	std::vector<unsigned int> indices;

	const aiVector3D ZeroVector(0.0f, 0.0f, 0.0f);


	std::vector<SubMesh> mesh_data = std::vector<SubMesh>();

	unsigned int BaseVertex = 0;
	unsigned int BaseIndex = 0;

	for (unsigned int meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
		const aiMesh* mesh = scene->mMeshes[meshIndex];

		glm::vec3 max = glm::vec3(-FLT_MAX);
		glm::vec3 min = glm::vec3(FLT_MAX);

		//create buffers
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
			const aiVector3D& pos = mesh->mVertices[i];
			const aiVector3D& normal = mesh->mNormals[i];
			const aiVector3D& tex = mesh->HasTextureCoords(0) ? mesh->mTextureCoords[0][i] : ZeroVector;

			//set min/max

			min.x = std::min(min.x, pos.x);
			min.y = std::min(min.y, pos.y);
			min.z = std::min(min.z, pos.z);

			max.x = std::max(max.x, pos.x);
			max.y = std::max(max.y, pos.y);
			max.z = std::max(max.z, pos.z);

			if (isSkeletal) {
				sVertices.emplace_back(pos, tex, normal);
			} else {
				vertices.emplace_back(pos, tex, normal);
			}

		}

		unsigned int maxIndex = 0;

		//create index buffer
		for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
			const aiFace& face = mesh->mFaces[i];

			if (face.mNumIndices != 3) {
				throw;
			}

			maxIndex = std::max(maxIndex, face.mIndices[0]);
			maxIndex = std::max(maxIndex, face.mIndices[1]);
			maxIndex = std::max(maxIndex, face.mIndices[2]);

			indices.insert(indices.end(), { face.mIndices[0] , face.mIndices[1] , face.mIndices[2] });
		}

		const unsigned int mNumIndices = mesh->mNumFaces * 3;

		mesh_data.push_back(SubMesh{ mNumIndices, BaseVertex, BaseIndex, mesh->mMaterialIndex, min, max });

		BaseIndex += mNumIndices;
		BaseVertex += mesh->mNumVertices;
	}

	/* ------------------------------ CALCULATE MIN/MAX/CENTER ------------------------------- */

	glm::vec3 max = glm::vec3(-FLT_MAX);
	glm::vec3 min = glm::vec3(FLT_MAX);

	for (int i = 0; i < mesh_data.size(); ++i) {
		min.x = std::min(min.x, mesh_data[i].min.x);
		min.y = std::min(min.y, mesh_data[i].min.y);
		min.z = std::min(min.z, mesh_data[i].min.z);

		max.x = std::max(max.x, mesh_data[i].max.x);
		max.y = std::max(max.y, mesh_data[i].max.y);
		max.z = std::max(max.z, mesh_data[i].max.z);
	}

	/* ------------------------------ IMPORT BONES / ANIMATIONS ------------------------------ */


	Skeleton* skeleton = nullptr;
	if (isSkeletal) { //HasSkeleton seems to generate false negatives so HasAnimations will just be used.
		skeleton = new Skeleton(scene->mRootNode, scene->mMeshes[0]);
	}
	
	
	std::vector<Animation*> animations;
	
	if (isSkeletal) {
		for (int i = 0; i < scene->mNumAnimations; ++i) {
			animations.push_back(new Animation(scene->mAnimations[i], skeleton));
		}
	}
	

	//this populates all vertex data with bone offsets
	if (isSkeletal) {
		for (int i = 0; i < scene->mNumMeshes; ++i) {
			const aiMesh* mesh = scene->mMeshes[i];

			for (int i = 0; i < mesh->mNumBones; ++i) {
				const aiBone* bone = mesh->mBones[i];


				for (int i = 0; i < bone->mNumWeights; ++i) {
					const aiVertexWeight& weight = bone->mWeights[i];

					if (weight.mWeight == 0) {
						continue;
					}

					sVertex& vertex = sVertices[weight.mVertexId];

					bool addedWeight = false;

					for (int i = 0; i < MAX_BONE_INFLUENCE; ++i) {
						if (vertex.boneIndices[i] == -1) {
							vertex.boneWeights[i] = weight.mWeight;

							int boneindex = skeleton->GetBone(bone->mName)->index;

							vertex.boneIndices[i] = boneindex;

							addedWeight = true;

							break;
						}
					}

					//remove lowest weight and normalize the rest.
					if (!addedWeight) {
						std::cout << "more than 4 bone weights" << std::endl;

						std::cout << "adding weight: " << weight.mWeight << ", index: " << skeleton->GetBone(bone->mName)->index << std::endl;

						float smallestWeight = weight.mWeight;
						int smallestWeightIndex = -1;

						float totalWeight = smallestWeight;

						for (int i = 0; i < MAX_BONE_INFLUENCE; ++i) {
							std::cout << "with weight: " << vertex.boneWeights[i] << ", index: " << vertex.boneIndices[i] << std::endl;
							if (vertex.boneWeights[i] < smallestWeight) {
								smallestWeight = vertex.boneWeights[i];
								smallestWeightIndex = i;
							}

							totalWeight += vertex.boneWeights[i];
						}

						totalWeight -= smallestWeight;

						for (int i = 0; i < MAX_BONE_INFLUENCE; ++i) {
							if (smallestWeightIndex == i) {
								vertex.boneWeights[i] = weight.mWeight;
								vertex.boneIndices[i] = skeleton->GetBone(bone->mName)->index;
							}

							vertex.boneWeights[i] /= totalWeight;
							std::cout << "finished with weight: " << vertex.boneWeights[i] << ", index: " << vertex.boneIndices[i] << std::endl;
						}

						//throw;
					}
				}
			}
		}
	}
	/* ----------------------------------- IMPORT TEXTURES ----------------------------------- */

	std::vector<Material*> materials;
	for (int i = 0; i < scene->mNumMaterials; i++) {
		materials.push_back(new Material(scene, i, path));
	}

	/* -------------------------------- GENERATE BOUNDING BOX -------------------------------- */

	StaticBoundingBox* sbb = BuildAABB(min, max);


	ModelData* CreatedData;
	if (isSkeletal) {
		CreatedData = new ModelData(sVertices, indices, mesh_data, materials, skeleton, animations, sbb);
	}
	else {
		CreatedData = new ModelData(vertices, indices, mesh_data, materials, skeleton, animations, sbb);
	}
	 

	return CreatedData;
}
