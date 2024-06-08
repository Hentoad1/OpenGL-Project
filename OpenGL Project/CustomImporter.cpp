#include "pch.h"

#include "CustomImporter.h"

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

		//reiquired: otherwise meshes will not align properly
		aiProcess_PreTransformVertices | \

		//does fix current issue but is good nonetheless
		aiProcess_GenUVCoords | \

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


			vertices.emplace_back(pos, tex, normal);

			min.x = std::min(min.x, pos.x);
			min.y = std::min(min.y, pos.y);
			min.z = std::min(min.z, pos.z);

			max.x = std::max(max.x, pos.x);
			max.y = std::max(max.y, pos.y);
			max.z = std::max(max.z, pos.z);
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

		mesh_data.push_back(SubMesh(BaseVertex, BaseIndex, mNumIndices, mesh->mMaterialIndex, min, max));

		BaseIndex += mesh->mNumFaces * 3;
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

	/* ----------------------------------- IMPORT TEXTURES ----------------------------------- */

	ModelData* CreatedData = new ModelData(vertices, indices, mesh_data, min, max);

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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buf[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data->indices[0]) * data->indices.size(), &data->indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);

	std::vector<MaterialBuffer> MBO = std::vector<MaterialBuffer>();

	for (int i = 0; i < data->Materials.size(); ++i) {
		MBO.emplace_back(data->Materials[i]);
	}

	ModelBuffers* CreatedData = new ModelBuffers{ VAO, MBO, data->mesh_data, data->min, data->max };

	mBuffers.push_back(CreatedData);
	
	return CreatedData;
}

ModelBuffers* CustomImporter::ImportAndAttach(const std::string& path) {
	ModelData* data = Import(path);
	ModelBuffers* buf = Attach(data);

	for (int i = 0; i < mData.size(); i++) {
		if (mData[i] == data) {
			delete data;
			mData.erase(mData.begin() + i);
			break;
		}
	}

	return buf;
}

CustomImporter::~CustomImporter() {
	for (int i = 0; i < mData.size(); ++i) {
		delete mData[i];
	}

	for (int i = 0; i < mBuffers.size(); ++i) {
		delete mBuffers[i];
	}
}

