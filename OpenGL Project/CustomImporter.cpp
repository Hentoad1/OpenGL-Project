#include "pch.h"

#include "CustomImporter.h"

#include "Bones.h"

ModelData* CustomImporter::Import(const std::string& path) {
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

		//max amounts of bones per vertex (defaults to 4)
		aiProcess_LimitBoneWeights | \

		//creates bone nodes for proper importing.
		aiProcess_PopulateArmatureData | \

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

	/* --------------------------------- CREATE BUFFER DATA ---------------------------------- */

	std::vector<Vertex> vertices;

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

			vertices.emplace_back(pos, tex, normal);
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
	
	
	Skeleton* skeleton = new Skeleton(scene->mRootNode, scene->mMeshes[0]);

	std::vector<Animation*> animations;

	for (int i = 0; i < scene->mNumAnimations; ++i) {
		animations.push_back(new Animation(scene->mAnimations[i], skeleton));
	}

	//this populates all vertex data

	for (int i = 0; i < scene->mNumMeshes; ++i) {
		const aiMesh* mesh = scene->mMeshes[i];
		
		for (int i = 0; i < mesh->mNumBones; ++i) {
			const aiBone* bone = mesh->mBones[i];


			for (int i = 0; i < bone->mNumWeights; ++i) {
				const aiVertexWeight& weight = bone->mWeights[i];
				Vertex& vertex = vertices[weight.mVertexId];

				for (int i = 0; i < MAX_BONE_INFLUENCE; ++i) {
					if (vertex.boneIndices[i] == -1) {
						vertex.boneWeights[i] = weight.mWeight;

						int boneindex = skeleton->GetBone(bone->mName)->index;

						std::cout << boneindex << std::endl;

						vertex.boneIndices[i] = boneindex;
						break;
					}
				}
			}
		}
	}

	

	/*for (int i = 0; i < vertices.size(); ++i) {
		std::cout << "-----------------------------" << std::endl;
		std::cout << vertices[i].boneIndices[0] << std::endl;
		std::cout << vertices[i].boneWeights[0] << std::endl;
		std::cout << vertices[i].boneIndices[1] << std::endl;
		std::cout << vertices[i].boneWeights[1] << std::endl;
		std::cout << vertices[i].boneIndices[2] << std::endl;
		std::cout << vertices[i].boneWeights[2] << std::endl;
		std::cout << vertices[i].boneIndices[3] << std::endl;
		std::cout << vertices[i].boneWeights[3] << std::endl;
	}*/

	/* ----------------------------------- IMPORT TEXTURES ----------------------------------- */

	ModelData* CreatedData = new ModelData(vertices, indices, mesh_data, skeleton, animations, min, max);

	for (int i = 0; i < scene->mNumMaterials; i++) {
		CreatedData->Materials.push_back(new Material(scene, i, path));
	}

	
	mData.push_back(CreatedData);


	return CreatedData;
}

ModelBuffers* CustomImporter::Attach(ModelData* data) {

	//populate VAO

	GLuint VAO;

	GLuint buf[2];

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(2, buf);

	size_t Vertex_Size = sizeof(data->vertices[0]);

	glBindBuffer(GL_ARRAY_BUFFER, buf[0]);
	glBufferData(GL_ARRAY_BUFFER, Vertex_Size * data->vertices.size(), &data->vertices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, Vertex_Size, 0);
	glEnableVertexAttribArray(POSITION_LOCATION);

	glVertexAttribPointer(TEXTURE_LOCATION, 2, GL_FLOAT, GL_FALSE, Vertex_Size, (void*)12);
	glEnableVertexAttribArray(TEXTURE_LOCATION);

	glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, Vertex_Size, (void*)20);
	glEnableVertexAttribArray(NORMAL_LOCATION);

	glVertexAttribIPointer(BONE_INDEX_LOCATION, 4, GL_INT, Vertex_Size, (void*)32);
	glEnableVertexAttribArray(BONE_INDEX_LOCATION);

	glVertexAttribPointer(BONE_WEIGHT_LOCATION, 4, GL_FLOAT, GL_FALSE, Vertex_Size, (void*)48);
	glEnableVertexAttribArray(BONE_WEIGHT_LOCATION);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data->indices[0]) * data->indices.size(), &data->indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	std::vector<MaterialBuffer*> MBO = std::vector<MaterialBuffer*>();

	for (int i = 0; i < data->Materials.size(); ++i) {
		MaterialBuffer* buf = new MaterialBuffer(data->Materials[i]);

		MBO.push_back(buf);
	}

	std::cout << "created: " << data->animations.size() << std::endl;

	ModelBuffers* CreatedData = new ModelBuffers{ VAO, MBO, data->mesh_data, data->skeleton, data->animations, data->min, data->max };

	mBuffers.push_back(CreatedData);
	
	return CreatedData;
}

ModelBuffers* CustomImporter::ImportAndAttach(const std::string& path) {
	ModelData* data = Import(path);
	ModelBuffers* buf = Attach(data);

	Free(data);

	return buf;
}


void CustomImporter::Free(void* ptr) {

	for (int i = 0; i < mData.size(); i++) {
		if (mData[i] == ptr) {
			delete mData[i];
			mData.erase(mData.begin() + i);
			return;
		}
	}

	for (int i = 0; i < mBuffers.size(); i++) {
		if (mBuffers[i] == ptr) {
			delete mBuffers[i];
			mBuffers.erase(mBuffers.begin() + i);
			return;
		}
	}

}

CustomImporter::~CustomImporter() {
	for (int i = 0; i < mData.size(); ++i) {
		delete mData[i];
	}

	for (int i = 0; i < mBuffers.size(); ++i) {
		delete mBuffers[i];
	}
}